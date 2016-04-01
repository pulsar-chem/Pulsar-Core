/*! \file
 *
 * \brief Exports for testing system
 * \author Benjamin Pritchard (ben@bennyp.org)
 */

#include "bpmodule/system/System.hpp"
#include "bpmodule/testing/TestSerialization.hpp"


namespace bpmodule {
namespace system {
namespace export_python {

void export_testing(pybind11::module & m)
{
    using bpmodule::testing::TestSerialization;

    /////////////////////////////////
    // Serialization
    /////////////////////////////////
    m.def("TestSerialization_BasisShellInfo",     &TestSerialization<BasisShellInfo>);
    m.def("TestSerialization_Atom",               &TestSerialization<Atom>);
}


} // close namespace export_python
} // close namespace system 
} // close namespace bpmodule