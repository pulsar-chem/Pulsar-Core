#ifndef MODULEINFO_H
#define MODULEINFO_H


#include "BPModule/python_helper/BoostPython_fwd.hpp"
#include "BPModule/datastore/OptionMap.hpp"


namespace bpmodule {
namespace modulestore {


struct ModuleInfo
{
    std::string key;
    std::string name;
    std::string type;
    std::string path;
    std::string soname;
    std::string version;
    std::vector<std::string> authors;
    std::string description;
    std::vector<std::string> refs;
    datastore::OptionMap options;

    ModuleInfo(void) = default;
    ModuleInfo(const ModuleInfo & rhs) = default;
    ModuleInfo(ModuleInfo && rhs) = default;
    ~ModuleInfo(void) = default;

    // for python
    ModuleInfo(const boost::python::dict & dictionary);
};


} // close namespace modulestore
} // close namespace bpmodule


#endif
