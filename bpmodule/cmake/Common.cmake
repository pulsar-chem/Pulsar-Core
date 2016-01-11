############################
# Paths and options for
# external dependencies
############################


# Don't use anything (ie, lib) as a prefix to SO
set(CMAKE_SHARED_MODULE_PREFIX "")



####################
# OpenMP is required
####################
find_package(OpenMP)
if(NOT OPENMP_FOUND) 
  message(FATAL_ERROR "Error - OpenMP is required!")
endif()

#######################
# Find MPI if requested
#######################
find_package(MPI)
if(NOT MPI_CXX_FOUND) 
  message(FATAL_ERROR "Cannot find MPI!")
endif()

# For some reason, this has a leading whitespace
string(STRIP "${MPI_CXX_LINK_FLAGS}" MPI_CXX_LINK_FLAGS)



############################
# Find boost headers
############################
find_package(Boost REQUIRED)



############################
# Find memwatch
############################
find_package(memwatch REQUIRED CONFIG)
include(${memwatch_CONFIG})


############################
# Find pybind11
############################
find_package(pybind11 REQUIRED CONFIG)
include(${pybind11_CONFIG})


############################
# Find libelemental
############################
find_package(libelemental REQUIRED CONFIG)
include(${libelemental_CONFIG})


############################
# Math libraries  
############################
find_package(LAPACK) # Also finds blas
if(NOT LAPACK_FOUND) 
  message(FATAL_ERROR "Error - LAPACK is required!")
endif()


############################
# Matrix library
############################
message(STATUS "Using libelemental from ${BPMODULE_LIBEL_PATH}")

