/*! \file
 *
 * \brief Loading and storing of C/C++ modules (source)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */


#include <dlfcn.h>

#include "bpmodule/modulemanager/CppModuleLoader.hpp"
#include "bpmodule/output/Output.hpp"
#include "bpmodule/modulemanager/ModuleManager.hpp"
#include "bpmodule/exception/Exceptions.hpp"
#include "bpmodule/exception/Assert.hpp"

using namespace bpmodule::exception;


namespace bpmodule {
namespace modulemanager {

CppModuleLoader::CppModuleLoader(ModuleManager * mm)
    : mm_(mm)
{ }



CppModuleLoader::~CppModuleLoader()
{
    // Finalization function in the so file
    typedef void (*FinalizeFunc)(void);

    // delete creator functions
    for(auto & it : soinfo_)
        it.second.creators.Clear();

    // close all the handles
    for(auto it : soinfo_)
    {
        void * handle = it.second.handle;

        output::Output("Closing %1%\n", it.first);
        FinalizeFunc ffn = reinterpret_cast<FinalizeFunc>(dlsym(handle, "FinalizeSupermodule"));

        // it's ok if it doesn't exist
        char const * error;
        if((error = dlerror()) != NULL)
            output::Debug("SO file %1% doesn't have finalization function. Skipping\n", it.first);
        else
        {
            output::Debug("Running finalization function in %1%\n", it.first);
            ffn();
        }

        // close the so
        dlclose(handle);
    }

    // clear everything else
    // (not needed. this is the destructor)
    //soinfo_.clear();
}



void CppModuleLoader::LoadSO(const ModuleInfo & minfo)
{
    // Initializing/Finalizing the so file
    typedef void (*InitializeFunc)(void);
    
    // Function for creating modules
    typedef ModuleCreationFuncs (*GeneratorFunc)(void);

    if(minfo.path == "")
        throw ModuleLoadException("Cannot open SO file - path not set in module info",
                                  "modulekey", minfo.key, "modulename", minfo.name);

    if(minfo.soname == "")
        throw ModuleLoadException("Cannot open SO file - module soname not set in module info",
                                  "modulekey", minfo.key, "path", minfo.path,
                                  "modulename", minfo.name);


    // trailing slash on path should have been added by python scripts
    std::string sopath = minfo.path + minfo.soname;

    ModuleCreationFuncs cf;

    // see if the module is loaded
    // if so, reuse that handle
    if(soinfo_.count(sopath) > 0)
        cf = soinfo_.at(sopath).creators;
    else
    {
        // first time loading this so file. Load it, get the
        // creators and run the initialization functions

        void * handle;
        char const * error; // for dlerror

        output::Debug("Looking to open so file: %1%\n", sopath);
        handle = dlopen(sopath.c_str(), RTLD_NOW | RTLD_GLOBAL);

        // open the module
        if(!handle)
            throw ModuleLoadException("Cannot open SO file",
                                      "path", sopath, "modulekey", minfo.key,
                                      "modulename", minfo.name, "dlerror", std::string(dlerror()));

        // 1.) Initialize the supermodule if the function exists
        InitializeFunc ifn = reinterpret_cast<InitializeFunc>(dlsym(handle, "InitializeSupermodule"));
        // it's ok if it doesn't exist
        if((error = dlerror()) != NULL)
            output::Debug("SO file %1% doesn't have initialization function. Skipping\n", sopath);
        else
        {
            output::Debug("Running initialization function in %1%\n", sopath);
            ifn();
        }
        


        // 2.) Module creator generation
        GeneratorFunc fn = reinterpret_cast<GeneratorFunc>(dlsym(handle, "InsertSupermodule"));
        if((error = dlerror()) != NULL)
        {
            dlclose(handle);
            throw ModuleLoadException("Cannot find InsertSupermodule function in SO file",
                                      "path", sopath, "modulekey", minfo.key,
                                      "modulename", minfo.name, "dlerror", error);
        }

        output::Success("Successfully opened %1%\n", sopath);

        cf = fn();

        SOInfo soinfo{handle, std::move(cf)};

        if(soinfo_.count(sopath) == 0)
            soinfo_.emplace(sopath, std::move(soinfo)); // only line that modifies this object
    }

    Assert<ModuleManagerException>(soinfo_.count(sopath) == 1, "CppModuleLoader SOInfo doesn't have just-added so file");

    mm_->InsertModule(soinfo_.at(sopath).creators, minfo);
}



} // close namespace modulemanager
} // close namespace bpmodule
