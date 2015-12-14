/*! \file
 *
 * \brief Python exports for module base classes
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#include "bpmodule/modulebase/All.hpp"
#include "bpmodule/datastore/Wavefunction.hpp"
#include "bpmodule/modulelocator/ModuleLocator.hpp"


using bpmodule::modulelocator::ModuleLocator;
using bpmodule::modulelocator::ModuleInfo;
using bpmodule::datastore::OptionMap;


namespace bpmodule {
namespace modulebase {
namespace export_python {

PYBIND11_PLUGIN(modulebase)
{
    pybind11::module m("modulebase", "Base classes for all modules");

    ///////////////////////
    // Module Base classes
    ///////////////////////
    //register_ptr_to_python<boost::shared_ptr<ModuleBase>>();

    // CallFunc doesn't need to be exported 
    pybind11::class_<ModuleBase> mbase(m, "ModuleBase");
    mbase.def("ID", &ModuleBase::ID)
         .def("Key", &ModuleBase::Key)
         .def("Name", &ModuleBase::Name)
         .def("Version", &ModuleBase::Version)
         .def("Print", &ModuleBase::Print)
         .def("MLocator", static_cast<ModuleLocator &(ModuleBase::*)(void) const>(&ModuleBase::MLocator), pybind11::return_value_policy::reference_internal) 
         .def("Options", static_cast<OptionMap &(ModuleBase::*)(void)>(&ModuleBase::Options), pybind11::return_value_policy::reference_internal)
         .def("Wfn", static_cast<datastore::Wavefunction &(ModuleBase::*)(void)>(&ModuleBase::Wfn), pybind11::return_value_policy::reference_internal) 
         .def("CreateChildModule", &ModuleBase::CreateChildModulePy)
         .def("Cache", &ModuleBase::Cache, pybind11::return_value_policy::reference_internal)
         ;


    /////////////////////////
    // Test class
    /////////////////////////
    //register_ptr_to_python<boost::shared_ptr<Test_Base>>();

    pybind11::class_<Test_Base_Py> testbase(m, "Test_Base", mbase);
    testbase.alias<Test_Base>()
            .def(pybind11::init<unsigned long>())
            .def("RunTest", &Test_Base::RunTest)
            .def("CallRunTest", &Test_Base::CallRunTest)
            .def("TestThrow", &Test_Base::TestThrow)
            .def("CallThrow", &Test_Base::CallThrow)
            ;


/*
    /////////////////////////
    // One electron integral implementation
    /////////////////////////
    register_ptr_to_python<boost::shared_ptr<OneElectronIntegralIMPL>>();

    //! \todo Don't know about from Calculate to python
    class_<OneElectronIntegralIMPL, bases<ModuleBase>, boost::noncopyable>("OneElectronIntegralIMPL", init<PyObject *, unsigned long>())
    .def("SetBases", &OneElectronIntegralIMPL::SetBases)
    .def("Calculate", &OneElectronIntegralIMPL::Calculate)
    .def("GetIntegralCount", &OneElectronIntegralIMPL::GetIntegralCount)
    .def("GetBuf", &OneElectronIntegralIMPL::GetBufPy)
    ;


    /////////////////////////
    // One electron integral builder
    /////////////////////////
    register_ptr_to_python<boost::shared_ptr<OneElectronIntegral>>();

    //! \todo Don't know about from Calculate to python
    class_<OneElectronIntegral, bases<ModuleBase>, boost::noncopyable>("OneElectronIntegral", init<PyObject *, unsigned long>())
    .def("SetBases", &OneElectronIntegral::SetBases)
    .def("Calculate", &OneElectronIntegral::Calculate)
    .def("GetIntegralCount", &OneElectronIntegral::GetIntegralCount)
    .def("GetBuf", &OneElectronIntegral::GetBufPy)
    ;


    /////////////////////////
    // Two electron integral implementation
    /////////////////////////
    register_ptr_to_python<boost::shared_ptr<TwoElectronIntegralIMPL>>();

    class_<TwoElectronIntegralIMPL, bases<ModuleBase>, boost::noncopyable>("TwoElectronIntegralIMPL", init<PyObject *, unsigned long>())
    .def("SetBases", &TwoElectronIntegralIMPL::SetBases)
    .def("Calculate", &TwoElectronIntegralIMPL::Calculate)
    .def("GetIntegralCount", &TwoElectronIntegralIMPL::GetIntegralCount)
    .def("GetBuf", &TwoElectronIntegralIMPL::GetBufPy)
    ;


    /////////////////////////
    // Two electron integral builder
    /////////////////////////
    register_ptr_to_python<boost::shared_ptr<TwoElectronIntegral>>();

    class_<TwoElectronIntegral, bases<ModuleBase>, boost::noncopyable>("TwoElectronIntegral", init<PyObject *, unsigned long>())
    .def("SetBases", &TwoElectronIntegral::SetBases)
    .def("Calculate", &TwoElectronIntegral::Calculate)
    .def("GetIntegralCount", &TwoElectronIntegral::GetIntegralCount)
    .def("GetBuf", &TwoElectronIntegral::GetBufPy)
    ;
*/

    return m.ptr();
}


} // close namespace export_python
} // close namespace modulebase
} // close namespace bpmodule

