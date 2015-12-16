#ifndef _GUARD_CREATORFUNCTIONS_HPP_
#define _GUARD_CREATORFUNCTIONS_HPP_

#include <functional>
#include <map>

#include "bpmodule/modulelocator/ModuleIMPLHolder.hpp"


namespace bpmodule {
namespace modulelocator {

typedef std::function<detail::ModuleIMPLHolder * (unsigned long)> ModuleCreatorFunc;
        

class CreatorFunctions
{
    public:
        CreatorFunctions() = default;
        ~CreatorFunctions() = default;

        CreatorFunctions(const CreatorFunctions & rhs) = default;
        CreatorFunctions & operator=(const CreatorFunctions & rhs) = default;
        CreatorFunctions(CreatorFunctions && rhs) = default;
        CreatorFunctions & operator=(CreatorFunctions && rhs) = default;


        /*! \brief Add a creator for a C++ module
         */ 
        template<typename T>
        void AddCppCreator(const std::string & name)
        {
            ModuleCreatorFunc cc = std::bind(&CreatorFunctions::CppConstructorWrapper<T>, std::placeholders::_1);
            creators_.emplace(name, cc);
        }


        /*! \brief Add a creator for a python module
         */ 
        void AddPyCreator(const std::string & name, pybind11::object cls)
        {
            ModuleCreatorFunc m = std::bind(&CreatorFunctions::PyConstructorWrapper, cls, std::placeholders::_1);
            creators_.emplace(name, m);
        }


        bool HasCreator(const std::string & key) const
        {
            return creators_.count(key);
        }


        ModuleCreatorFunc GetCreator(const std::string & key) const
        {
            //! \todo exceptions
            return creators_.at(key);
        }

    private:

        std::map<std::string, ModuleCreatorFunc> creators_;


        /*! \brief Wrap construction of a C++ object
         */ 
        template<typename T>
        static
        detail::ModuleIMPLHolder *
        CppConstructorWrapper(unsigned long i)
        {
            std::unique_ptr<typename T::BaseType> p(new T(i));
            return new detail::CppModuleIMPLHolder<typename T::BaseType>(std::move(p));
        }


        /*! \brief Wrap construction of a python object
         */ 
        static
        detail::ModuleIMPLHolder *
        PyConstructorWrapper(pybind11::object cls, unsigned long i)
        {
            pybind11::object o = cls.call(i);
            detail::ModuleIMPLHolder * ret = new detail::PyModuleIMPLHolder(o);
            return ret;
        }
};


} // close namespace modulelocator
} // close namespace bpmodule


#endif
