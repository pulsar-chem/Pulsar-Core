/*! \file
 *
 * \brief Calling of python functions (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#ifndef _GUARD_CALL_HPP_
#define _GUARD_CALL_HPP_

#include "bpmodule/exception/PythonCallException.hpp"
#include "bpmodule/python/Errors.hpp"
#include "bpmodule/python/Convert.hpp"


namespace bpmodule {
namespace python {


/*! \brief Calls a python object
 *
 * \throw bpmodule::exception::PythonCallException if there is an error (including conversion error)
 *
 * \param [in] obj The python object to call
 */
template<typename Ret, typename... Targs>
Ret CallPyFunc(pybind11::object obj, Targs... Fargs)
{
    using bpmodule::exception::PythonCallException;
    using bpmodule::exception::PythonConvertException;
    using bpmodule::exception::GeneralException;
    using bpmodule::exception::Assert;

    Assert<GeneralException>(obj.ptr() != nullptr, "Python object pointer is null");

    int nargs = static_cast<int>(sizeof...(Fargs));

    // don't check for nargs, since this may be a class method
    // and Fargs... doesn't include self
    if(!IsCallable(obj))  
        throw PythonCallException("Object is not callable!", "nargs", nargs);

    pybind11::object ret;


    try {
        ret = obj.call(Fargs...);
    }
    catch(const std::exception & ex)
    {
        throw PythonCallException(detail::GetPyException(),
                                  "when", "In a python function");
    }
    catch(...)
    {
        throw PythonCallException("Caught unknown exception when calling a python function");
    }



    try {
        return ConvertToCpp<Ret>(ret);
    }
    catch(const PythonConvertException & ex)
    {
        // change to a PythonCallException
        throw PythonCallException(ex,
                                  "desc", "Unable to convert return value from python function");
    }
}





/*! \brief Calls a function that is an attribute a python object
 *
 * \throw bpmodule::exception::PythonCallException if there is an error, including
 *        if the object does not have the given attribute or if there is a conversion
 *        error
 *
 * \param [in] obj The object with the attribute
 * \param [in] attribute The attribute to call
 */
template<typename Ret, typename... Targs>
Ret CallPyFuncAttr(pybind11::object obj, const char * attribute, Targs... Fargs)
{
    using bpmodule::exception::PythonCallException;
    using bpmodule::exception::GeneralException;
    using bpmodule::exception::Assert;

    Assert<GeneralException>(obj.ptr() != nullptr, "Python object pointer is null");

    int nargs = static_cast<int>(sizeof...(Fargs));

    if(!HasCallableAttr(obj, attribute))
        throw PythonCallException("Object does not have callable attribute!",
                                  "function", attribute,
                                  "nargs", nargs);

    return CallPyFunc<Ret>(static_cast<pybind11::object>(obj.attr(attribute)), Fargs...); 
}




} // close namespace python
} // close namespace bpmodule

#endif
