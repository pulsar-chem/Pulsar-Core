#ifndef MODULEBASE_H
#define MODULEBASE_H

#include <string>
#include <functional>
#include <iostream>

#include "BPModule/core/ModuleInfo.h" // includes optionmap

namespace bpmodule {

class ModuleStore;


class ModuleBase
{
public:
  ModuleBase(long id, ModuleStore * mstore, const OptionMap & options);

  virtual ~ModuleBase() { }

  ModuleBase(const ModuleBase & rhs) = delete;
  ModuleBase(ModuleBase && rhs) = delete;
  ModuleBase & operator= (const ModuleBase & rhs) = delete;
  ModuleBase & operator= (ModuleBase && rhs) = delete;

  template<typename T>
  const T & GetTrait(const std::string & key) const
  {
    return traits_.Get<T>(key);
  }

  bool HasTrait(const std::string & key) const
  {
    return traits_.Has(key);
  }

  template<typename T>
  const T & GetOption(const std::string & key) const
  {
    return options_.Get<T>(key);
  }

  bool HasOption(const std::string & key) const
  {
    return options_.Has(key);
  }

  template<typename T>
  void SetOption(const std::string & key, const T & value)
  {
    options_.Set(key, value);
  }

  void Dump(void) const;

  std::string MyKey(void) const;

  void Help(void) const;

  ModuleInfo MyInfo(void) const;

protected:
  ModuleStore & mstore_;
  std::ostream & out_;

  template<typename T>
  void SetTrait(const std::string & key, const T & value)
  {
    traits_.Set(key, value);
  }

private:
  long id_;
  OptionMap traits_;
  OptionMap options_;
};


} // close namespace bpmodule

#endif
