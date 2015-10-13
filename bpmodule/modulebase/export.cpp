/*! \file
 *
 * \brief Python exports for module base classes
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/register_ptr_to_python.hpp>
#include <boost/python/pure_virtual.hpp>

#include "bpmodule/modulebase/All.hpp"
#include "bpmodule/modulebase/All_python.hpp"
#include "bpmodule/modulestore/ModuleStore.hpp"


using bpmodule::modulestore::ModuleStore;
using bpmodule::modulestore::ModuleInfo;
using bpmodule::options::OptionMap;

using namespace boost::python;



namespace bpmodule {
namespace modulebase {
namespace export_python {


BOOST_PYTHON_MODULE(modulebase)
{
    ///////////////////////
    // Module Base classes
    ///////////////////////
    // python should never derive from ModuleBase, so a constructor should not be needed
    class_<ModuleBase, boost::noncopyable>("ModuleBase", no_init)
//    .def("MStore", &ModuleBase::MStore, return_internal_reference<>())
    .def("ID", &ModuleBase::ID)
    .def("Key", &ModuleBase::Key, return_value_policy<copy_const_reference>())
    .def("Name", &ModuleBase::Name, return_value_policy<copy_const_reference>())
    .def("Version", &ModuleBase::Version, return_value_policy<copy_const_reference>())
    .def("Print", &ModuleBase::Print)
    .def("Options", static_cast<OptionMap &(ModuleBase::*)(void)>(&ModuleBase::Options), return_value_policy<reference_existing_object>());  // should be safe?



    register_ptr_to_python<boost::shared_ptr<Test_Base>>();
    class_<Test_Base_Wrap, bases<ModuleBase>, boost::shared_ptr<Test_Base_Wrap>, boost::noncopyable>("Test_Base", init<unsigned long, ModuleStore &, ModuleInfo &>())
    .def("MStore", &Test_Base_Wrap::MStore, return_value_policy<reference_existing_object>()) 
    .def("RunTest", pure_virtual(&Test_Base::RunTest))
    .def("CallRunTest", pure_virtual(&Test_Base::CallRunTest))
    .def("Throw", pure_virtual(&Test_Base::Throw))
    .def("CallThrow", pure_virtual(&Test_Base::CallThrow))
    .def("CalcTest", pure_virtual(&Test_Base::CalcTest), return_value_policy<return_by_value>());

}


} // close namespace export_python
} // close namespace modulebase
} // close namespace bpmodule

