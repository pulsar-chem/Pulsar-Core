/*! \file
 *
 * \brief Mangling/Demangling helpers (source) 
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#include <cxxabi.h>
#include "pulsar/util/Mangle.hpp"

namespace pulsar{

std::string demangle_cpp(const char * typestr)
{
    // taken from https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html

    int status;
    char * realname;

    // by default, return typestr, unless the
    // demangling fails. Should it ever?
    std::string ret(typestr);

    realname = abi::__cxa_demangle(typestr, NULL, NULL, &status);

    if(status == 0)
        ret = std::string(realname);

    free(realname);

    return ret;   
}


std::string demangle_cpp(const std::string & typestr)
{
    return demangle_cpp(typestr.c_str());
}

} // close namespace pulsar
