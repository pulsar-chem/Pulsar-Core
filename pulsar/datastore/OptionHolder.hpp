/*! \file
 *
 * \brief Storage of options data (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#ifndef PULSAR_GUARD_DATASTORE__OPTIONHOLDER_HPP_
#define PULSAR_GUARD_DATASTORE__OPTIONHOLDER_HPP_

#include <functional>

#include "pulsar/datastore/OptionBase.hpp"
#include "pulsar/datastore/OptionTypes.hpp"
#include "pulsar/datastore/OptionHolder_printing.hpp"
#include "pulsar/util/Serialization.hpp"
#include "pulsar/python/Call.hpp"
#include "pulsar/output/Output.hpp"

#include "pulsar/util/bphash/types/memory.hpp"

namespace pulsar{
namespace datastore {
namespace detail {


// forward declaration
template<OptionType OPTTYPE> class OptionHolder;



/*! \brief Creates an OptionHolder based on an OptionType
 *
 * Passes the rest of the arguments to the OptionHolder constructor
 */
OptionBasePtr
CreateOptionHolder(std::string key, OptionType opttype, bool required,
                   const pybind11::object & validator, std::string help,
                   const pybind11::object & def);

/*! \brief Creates an OptionHolder based on an OptionType
 *
 * Passes the rest of the arguments to the OptionHolder constructor
 */
OptionBasePtr
OptionHolderFromByteArray(OptionType opttype, const ByteArray & ba);



/*! \brief A wrapper around a python validation function
 *
 * Will call the python function \p func and give it \p val as its only argument
 *
 * \throw pulsar::exception::PythonCallException if there is a problem calling
 *        the python function or if the return type can't be converted
 *
 */
template<OptionType OPTTYPE>
static OptionIssues ValidatorWrapper_(pybind11::object & valobj,
                                      const std::string & key,
                                      const OptionHolder<OPTTYPE> & value)
{
    try {
        if(!valobj || python::IsNone(valobj))
            return {};
        return python::CallPyFuncAttr<OptionIssues>(valobj, "Validate", value.GetPy());
    }
    catch(const std::exception & ex)
    {
        throw exception::OptionException(ex, "optionkey", key,
                                         "when", "Attempting to validate an option");
    }
}




/*! \brief Holds the value and default for an option
 *
 * \note This is a template class, but definitions are in the
 *       cpp file. This class is then defined for the
 *       allowed option types.
 */
template<OptionType OPTTYPE>
class OptionHolder : public OptionBase
{
    public:
        //! The type I'm storing
        typedef typename OptionTypeInfo<OPTTYPE>::stored_type stored_type;


        //! A function that can validate me
        typedef std::function<OptionIssues (const OptionHolder<OPTTYPE> &)> ValidatorFunc;


        /*! \brief Constructs without a default
         *
         * This object will take ownership of the value and def pointers.
         * The default value will be validated (if given).
         *
         * The value is not set on construction, only the default
         *
         * \throw pulsar::exception::OptionException
         *        If the default value is invalid, or
         *        there is a default argument supplied for a 'required' option.
         *
         * \throw pulsar::exception::PythonCallException
         *       If there is a problem calling the validation function
         *
         * \param [in] key The key of this option
         * \param [in] validator A validator function for this object
         * \param [in] required True if this option is required
         * \param [in] help A help string for this option
         *
         */
        OptionHolder(const std::string & key,
                     bool required, const pybind11::object & validator,
                     const std::string & help)
                : OptionHolder(key, required, validator, help, nullptr)
        {  }

        OptionHolder(const std::string & key,
                     bool required, const pybind11::object & validator,
                     const std::string & help, const stored_type & def)
            : OptionHolder(key, required, validator, help, new stored_type(def))
        {
            using exception::OptionException;

            if(required)
                throw OptionException("Default value supplied for required option",
                                      "optionkey", Key());

            // check the default using the validator
            OptionIssues iss = GetIssues();
            if(iss.size())
                throw OptionException("Default value for this option does not pass validation",
                                      "optionkey", Key(), "issues", iss);

        }

        OptionHolder(const std::string & key,
                     bool required, const pybind11::object & validator,
                     const std::string & help, const pybind11::object & def)
            : OptionHolder(key, required, validator, help,
                           python::ConvertToCpp<stored_type>(def))
        {
        }



        /*! \brief Copy constructor
         *
         * Data will be deep copied
         */
        OptionHolder(const OptionHolder & oph)
            : OptionBase(oph), validator_(oph.validator_)
        {
            if(oph.value_)
                value_ = std::unique_ptr<stored_type>(new stored_type(*oph.value_));
            if(oph.default_)
                default_ = std::unique_ptr<stored_type>(new stored_type(*oph.default_));
        }




        OptionHolder(void)                                  = delete;
        OptionHolder(OptionHolder && oph)                   = delete;
        OptionHolder & operator=(const OptionHolder & oph)  = delete;
        OptionHolder & operator=(OptionHolder && oph)       = delete;
        virtual ~OptionHolder() { } // Cannot be default due to compiler bugs



        /*! \brief Change the stored value
         *
         * This object will copy construct a new value
         *
         * \exstrong
         */
        void Change(const stored_type & value)
        {
            value_ = std::unique_ptr<stored_type>(new stored_type(value));
        }



        /*! \brief Get the current value
         *
         * If the value is not set, but a default exists, the default is returned.
         *
         * \throw pulsar::exception::OptionException
         *        If the option does not have a value or a default
         */
        const stored_type & Get(void) const
        {
            if(value_)
                return *value_;
            else if(default_)
                return *default_;
            else
                throw exception::OptionException("Option does not have a value",
                                                 "optionkey", Key());
        }



        /*! \brief Get the default value
         *
         * \throw pulsar::exception::OptionException
         *        If the option does not have a default
         */
        const stored_type & GetDefault(void) const
        {
            if(default_)
                return *default_;
            else
                throw exception::OptionException("Option does not have a default",
                                                 "optionkey", Key());
        }



        ////////////////////////////////////////
        // Virtual functions from OptionBase
        ////////////////////////////////////////

        virtual OptionBasePtr Clone(void) const
        {
            return OptionBasePtr(new OptionHolder<OPTTYPE>(*this));
        }

        virtual const char * TypeString(void) const noexcept
        {
            return OptionTypeToString(OPTTYPE);
        }

        virtual OptionType Type(void) const noexcept
        {
            return OPTTYPE;
        }

        virtual bool HasValue(void) const noexcept
        {
            return bool(value_) || bool(default_);
        }

        virtual bool HasDefault(void) const noexcept
        {
            return bool(default_);
        }

        virtual bool IsSet(void) const noexcept
        {
            return bool(value_);
        }

        virtual bool IsDefault(void) const
        {
            if(!value_ && default_)
                return true;
            else
            {
                // ignore compiler warnings about floating point equality
                PRAGMA_WARNING_PUSH
                PRAGMA_WARNING_IGNORE_FP_EQUALITY

                return value_ && default_ && (*value_ == *default_);

                PRAGMA_WARNING_POP
            }
        }

        virtual void ResetToDefault(void) noexcept
        {
            value_.reset();
        }


        virtual void Print(std::ostream & os) const
        {
            using namespace pulsar::output;
            using namespace pulsar::util;

            std::vector<std::string> val = {"(none)"};
            std::vector<std::string> def = {"(none)"};

            if(default_)
                def = OptToString(*default_);

            if(value_)
                val = OptToString(*value_);
            else if(default_)
                val = def;

            // pad out
            size_t m = std::max(val.size(), def.size());
            val.resize(m);
            def.resize(m);

            std::string req = (IsRequired() ? "True" : "False");
            std::string isset = (IsSet() ? "True" : "False");

            // print the first line
            std::vector<std::string> optlines;
            optlines.push_back(FormatString("    %-20?   %-20?   %-8?   %-20?   %-20?   %-8?   %?\n",
                                            Key(), TypeString(), isset, val[0], def[0], req,  Help()));


            // now other lines
            for(size_t i = 1; i < m; i++)
            {
                optlines.push_back(FormatString("    %-20?   %-20?   %-8?   %-20?   %-20?   %-8?   %?\n",
                                                "", "", "", val[i], def[i], "", ""));
            }
           
            // now actually print 
            for(const auto & it : optlines)
            {
                OutputType type = OutputType::Output;

                if(!IsSetIfRequired())
                    type = OutputType::Error;
                else if(!IsDefault())
                    type = OutputType::Changed;

                GeneralOutput(os, type, it);
            }
        }


        virtual OptionIssues GetIssues(void) const
        {
            if(!IsSetIfRequired())
                return OptionIssues{"Option is not set, but is required"};
            else if(validator_)
                return validator_(*this);
            else
                return OptionIssues();
        }

        virtual bool Compare(const OptionBase & rhs) const
        {
            const OptionHolder<OPTTYPE> * op = dynamic_cast<const OptionHolder<OPTTYPE> *>(&rhs);

            if(op == nullptr) // option of a different type
                return false;

            PRAGMA_WARNING_PUSH
            PRAGMA_WARNING_IGNORE_FP_EQUALITY

            if(! (this->IsSet() == op->IsSet() &&
                  this->HasDefault() == op->HasDefault()) )
                return false;

            // we checked above that they are both set and unset
            if(this->IsSet() && *value_ != *(op->value_))
                return false;

            if(this->HasDefault() && *default_ != *(op->default_))
                return false;

            return true;
            PRAGMA_WARNING_POP
        }

        virtual ByteArray ToByteArray(void) const
        {
            util::MemoryArchive mar;
            mar.BeginSerialization();
            mar.Serialize(Key(), IsRequired(), Help(), value_, default_);
            mar.EndSerialization();
            return mar.ToByteArray();
        }


        /////////////////////////////////////////
        // Python-related functions
        /////////////////////////////////////////
        virtual pybind11::object GetPy(void) const
        {
            try {                                                     
                return python::ConvertToPy(Get());                            
            }                                                         
            catch(std::exception & ex)                                
            {                                                         
                throw exception::OptionException(ex, "optionkey", Key());        
            }                                                         

        }

        virtual void ChangePy(const pybind11::object & obj)
        {
            stored_type val;

            try {
                val = python::ConvertToCpp<stored_type>(obj);
            }
            catch(std::exception & ex)
            {
                throw exception::OptionException(ex, "optionkey", Key());
            }

            Change(val);
        }


    private:
        friend OptionBasePtr OptionHolderFromByteArray(OptionType, const ByteArray &);

        // used in constructor delegation
        OptionHolder(const std::string & key,
                     bool required, const pybind11::object & validator,
                     const std::string & help, stored_type * def)
            : OptionBase(key, required, help), default_(def)
        {
            validator_ = std::bind(ValidatorWrapper_<OPTTYPE>, validator, Key(),
                                   std::placeholders::_1);
        }

        // used in deserialization
        OptionHolder(std::string && key,bool required, 
                     std::string && help,
                     std::unique_ptr<stored_type> && value,
                     std::unique_ptr<stored_type> && def)
            : OptionBase(std::move(key), required, std::move(help)),
              value_(std::move(value)), default_(std::move(def))
        {  }


        //! A set value for the option
        std::unique_ptr<stored_type> value_;

        //! The default for the option
        std::unique_ptr<stored_type> default_;

        //! Validation function object
        ValidatorFunc validator_;


        //! \name Hashing and Serialization
        ///@{

        DECLARE_HASHING_FRIENDS

        void hash(util::Hasher & h) const
        {
            OptionBase::hash(h);
            h(value_, default_);
        }


        void hash_value(util::Hasher & h) const
        {
            h(static_cast<const OptionBase &>(*this));

            if(HasValue())
                h(Get());
            else
                h(std::string("__!%_NOVALUE_%!__"));
        }


        ///@}
};


///////////////////////////////////////////////////
// These are the allowed types of OptionHolder
///////////////////////////////////////////////////
extern template class OptionHolder<OptionType::Int>;
extern template class OptionHolder<OptionType::Float>;
extern template class OptionHolder<OptionType::Bool>;
extern template class OptionHolder<OptionType::String>;

extern template class OptionHolder<OptionType::ListInt>;
extern template class OptionHolder<OptionType::ListFloat>;
extern template class OptionHolder<OptionType::ListBool>;
extern template class OptionHolder<OptionType::ListString>;

extern template class OptionHolder<OptionType::SetInt>;
extern template class OptionHolder<OptionType::SetFloat>;
extern template class OptionHolder<OptionType::SetBool>;
extern template class OptionHolder<OptionType::SetString>;

extern template class OptionHolder<OptionType::DictIntInt>;
extern template class OptionHolder<OptionType::DictIntFloat>;
extern template class OptionHolder<OptionType::DictIntBool>;
extern template class OptionHolder<OptionType::DictIntString>;

extern template class OptionHolder<OptionType::DictStringInt>;
extern template class OptionHolder<OptionType::DictStringFloat>;
extern template class OptionHolder<OptionType::DictStringBool>;
extern template class OptionHolder<OptionType::DictStringString>;

        


} // close namespace detail
} // close namespace datastore
} // close namespace pulsar


#endif