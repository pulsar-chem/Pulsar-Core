/*! \file
 *
 * \brief Storage of options for a module (source)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */

#include <boost/python/dict.hpp>
#include "bpmodule/python_helper/Convert.hpp"
#include "bpmodule/python_helper/Call.hpp"


#include "bpmodule/options/OptionMap.hpp"
#include "bpmodule/output/Output.hpp"


using bpmodule::python_helper::ConvertToCpp;
using bpmodule::python_helper::DeterminePyType;
using bpmodule::python_helper::GetPyClass;
using bpmodule::exception::OptionException;
using bpmodule::output::Output;


namespace bpmodule {
namespace options {



////////////////////////////////////////////////
// Member functions
////////////////////////////////////////////////

OptionMap::OptionMap(const OptionMap & rhs)
    : expert_(rhs.expert_),
      wholevalid_(rhs.wholevalid_)

{
    for(const auto & it : rhs.opmap_)
        opmap_.emplace(it.first, detail::OptionBasePtr(it.second->Clone()));
}


OptionMap & OptionMap::operator=(const OptionMap & rhs)
{
    if(this != &rhs)
    {
        expert_ = rhs.expert_;
        wholevalid_ = rhs.wholevalid_;

        opmap_.clear();
        for(const auto & it : rhs.opmap_)
            opmap_.emplace(it.first, detail::OptionBasePtr(it.second->Clone()));
    }
    return *this;
}


bool OptionMap::Has(const std::string & key) const
{
    if(opmap_.count(key) == 0)
        return false;
    return opmap_.at(key)->HasValue();
}


bool OptionMap::HasKey(const std::string & key) const
{
    return opmap_.count(key);
}

size_t OptionMap::Size(void) const noexcept
{
    return opmap_.size();
}


bool OptionMap::IsDefault(const std::string & key) const
{
    return GetOrThrow_(key)->IsDefault();
}

void OptionMap::ResetToDefault(const std::string & key)
{
    GetOrThrow_(key)->ResetToDefault();
}


bool OptionMap::AllReqSet(void) const noexcept
{
    for(const auto & it : opmap_)
        if(!it.second->IsSetIfRequired())
            return false;
    return true;
}

void OptionMap::SetExpert(bool expert) noexcept 
{
    expert_ = expert;
    for(const auto & it : opmap_)
        it.second->SetExpert(expert);
}
        

std::vector<std::string> OptionMap::AllMissingReq(void) const
{
    std::vector<std::string> req;
    for(const auto & it : opmap_)
        if(!it.second->IsSetIfRequired())
            req.push_back(it.first);

    return req;
}


detail::OptionBase * OptionMap::GetOrThrow_(const std::string & key)
{
    if(opmap_.count(key))
        return opmap_.at(key).get();
    else
        throw OptionException("Key not found", key);
}


const detail::OptionBase * OptionMap::GetOrThrow_(const std::string & key) const
{
    if(opmap_.count(key))
        return opmap_.at(key).get();
    else
        throw OptionException("Key not found", key);
}


static bool WholeOptValidatorWrapper(const boost::python::object & val, const OptionMap & op)
{
    return boost::python::extract<bool>(python_helper::CallPyFunc(val, op));
}


//////////////////////////////
// Python functions
//////////////////////////////
OptionMap::OptionMap(const boost::python::dict & opt, const boost::python::object & wholevalidfunc)
{
    boost::python::list keys = opt.keys();

    // shouldn't throw, should it?
    int keylen = boost::python::extract<int>(keys.attr("__len__")());

    for(int i = 0; i < keylen; i++)
    {
        if(DeterminePyType(keys[i]) != python_helper::PythonType::String)
            throw OptionException("Key in OptionMap dictionary is not a string", "(unknown)",
                                  "element", std::to_string(i),
                                  "pytype", GetPyClass(keys[i]));


        std::string key = ConvertToCpp<std::string>(keys[i]);

        // convert to lowercase
        output::ToLower(key);
        

        // should this ever happen? Keys should be unique in a
        //  python dict
        if(opmap_.count(key))
            throw OptionException("Duplicate key on construction", key,
                                   "element", std::to_string(i));

        // this will throw needed exceptions
        opmap_.emplace(key, detail::OptionHolderFactory(key, opt[key]));
    }

    // add whole validator (if it exists)
    if(DeterminePyType(wholevalidfunc) != python_helper::PythonType::None)
    {
        // Don't forget that the method is part of a class
        // so 1 argument is "self"
        if(!python_helper::HasCallableAttr(wholevalidfunc, "Validate", 2)) 
                throw OptionException("Whole options validator does not have a callable Validate() method taking one argument", "(none)",
                                      "pytype", GetPyClass(wholevalidfunc));

        wholevalid_ = std::bind(WholeOptValidatorWrapper, wholevalidfunc, std::placeholders::_1);
    }

}



void OptionMap::ChangePy(const std::string & key, const boost::python::object & obj)
{
    detail::OptionBase * ptr = GetOrThrow_(key);
    ptr->ChangePy(obj);
}



void OptionMap::ChangePyDict(const boost::python::dict & opt)
{
    using std::swap;

    boost::python::list keys = opt.keys();
    int keylen = boost::python::extract<int>(keys.attr("__len__")());

    // for strong exception guarantee:
    // copy the current object, modify that, then swap

    OptionMap tmp(*this);

    for(int i = 0; i < keylen; i++)
    {
        if(DeterminePyType(keys[i]) != python_helper::PythonType::String)
            throw OptionException("Cannot convert python dictionary index to string", "(unknown)", 
                                  "element", std::to_string(i),
                                  "pytype", GetPyClass(keys[i]));

        std::string key = ConvertToCpp<std::string>(keys[i]);

        if(!tmp.HasKey(key))
            throw OptionException("Python dictionary has a key that I do not", key, "element", std::to_string(i));

        tmp.ChangePy(key, opt[key]);
    }

    swap(*this, tmp);
}



boost::python::object OptionMap::GetPy(const std::string & key) const
{
    return GetOrThrow_(key)->GetPy();
}






//////////////////////////////////////
// Printing of options
/////////////////////////////////////
void OptionMap::Print(void) const
{
    size_t nopt = Size();
    if(nopt > 0)
    {
        Output("\n");
        std::string s20(20, '-');
        std::string s10(10, '-');
        Output("          %|1$-20|      %|2$-20|      %|3$-20|      %|4$-20|     %|5$-10|       %6%\n", "Option", "Type", "Value", "Default", "Required", "Description");
        Output("          %|1$-20|      %|2$-20|      %|3$-20|      %|4$-20|     %|5$-10|       %6%\n", s20, s20, s20, s20, s10, s20);

        for(const auto & it : opmap_)
            it.second->Print();
    }
    Output("\n");
}







} // close namespace options
} // close namespace bpmodule

