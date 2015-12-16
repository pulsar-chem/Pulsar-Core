/*! \file
 *
 * \brief Base class for a test module (header)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#ifndef _GUARD_TEST_BASE_HPP_
#define _GUARD_TEST_BASE_HPP_

#include "bpmodule/modulebase/ModuleBase.hpp"


namespace bpmodule {
namespace modulebase {

/*! \brief A test module
 *
 * Just to make sure the library works
 */
class Test_Base : public ModuleBase
{
    public:
        typedef Test_Base BaseType;


        Test_Base(unsigned long id)
            : ModuleBase(id)
        { }


        /*! \brief Just test some functionality
         */
        void RunTest(void)
        {
            return ModuleBase::CallFunction(&Test_Base::RunTest_);
        }


        /*! \brief Call RunTest() of another module
         *
         * \param [in] other Key of the other module in the database
         */ 
        void CallRunTest(const std::string & other)
        {
            return ModuleBase::CallFunction(&Test_Base::CallRunTest_, other);
        }



        /*! \brief Throw an exception
         */
        void TestThrow(void)
        {
            return ModuleBase::CallFunction(&Test_Base::TestThrow_);
        }



        /*! \brief Call Throw() of another module
         *
         * \param [in] other Key of the other module in the database
         */ 
        void CallThrow(const std::string & other)
        {
            return ModuleBase::CallFunction(&Test_Base::CallThrow_, other);
        }




        /////////////////////////////////////////
        // To be implemented by derived classes
        /////////////////////////////////////////
        /*! \copydoc RunTest
         * 
         * \note To be implemented by derived classes
         */ 
        virtual void RunTest_(void) = 0;


        /*! \copydoc CallRunTest
         * 
         * \note To be implemented by derived classes
         */ 
        virtual void CallRunTest_(const std::string & other) = 0;


        /*! \copydoc TestThrow
         * 
         * \note To be implemented by derived classes
         */ 
        virtual void TestThrow_(void) = 0;


        /*! \copydoc CallThrow
         * 
         * \note To be implemented by derived classes
         */ 
        virtual void CallThrow_(const std::string & other) = 0;


};




class Test_Base_Py : public Test_Base
{
    public:
        using Test_Base::Test_Base;

    
        virtual void RunTest_(void)
        {
            PYBIND11_OVERLOAD_PURE(void, Test_Base, RunTest_);
        }



        virtual void CallRunTest_(const std::string & other)
        {
            PYBIND11_OVERLOAD_PURE(void, Test_Base, CallRunTest_, other);
        }



        virtual void TestThrow_(void)
        {
            PYBIND11_OVERLOAD_PURE(void, Test_Base, TestThrow_); 
        }



        virtual void CallThrow_(const std::string & other)
        {
            PYBIND11_OVERLOAD_PURE(void, Test_Base, CallThrow_, other);
        }

};


} // close namespace modulebase
} // close namespace bpmodule

#endif
