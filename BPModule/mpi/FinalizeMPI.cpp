#include "BPModule/core/Output.hpp"
#include "BPModule/mpi/MPI.hpp"

#include <boost/python.hpp>
#include <mpi.h>

namespace out = bpmodule::output;
namespace bpy = boost::python;

namespace bpmodule {
namespace mpi {

void FinalizeMPI(void)
{
    out::Output("Finalizing Process %1% of %2%\n", GetProcID(), GetNProc());
    MPI_Finalize();
}


} // close namespace mpi
} // close namespace bpmodule
