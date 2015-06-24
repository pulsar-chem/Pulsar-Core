#ifndef MODULEINFO_H
#define MODULEINFO_H

#include <string>
#include <vector>

#include "BPModule/core/OptionMap.h"

namespace bpmodule {


struct ModuleInfo
{
  std::string name;
  std::string type;
  std::string path;
  std::string soname;
  std::string version;
  std::vector<std::string> authors;
  std::string description;
  std::vector<std::string> refs;
  OptionMap options;
};


} // close namespace bpmodule


#endif
