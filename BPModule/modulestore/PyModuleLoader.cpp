#include "BPModule/output/Output.hpp"
#include "BPModule/modulestore/PyModuleLoader.hpp"
#include "BPModule/modulestore/ModuleStore.hpp"
#include "BPModule/modulebase/ModuleBase.hpp"


namespace bpmodule {
namespace modulestore {



PyModuleLoader::PyModuleLoader(ModuleStore * mst)
    : mst_(mst)
{
}



PyModuleLoader::~PyModuleLoader()
{
    UnloadAll();
}



modulebase::ModuleBase * PyModuleLoader::CreateWrapper_(boost::python::object fn, const std::string & key,
                                            unsigned long id,
                                            const modulestore::ModuleInfo & minfo)
{
    boost::python::object newobj = fn(key, id, boost::ref(*mst_), boost::ref(minfo));
    objects_[id] = newobj;
    return boost::python::extract<modulebase::ModuleBase *>(newobj);
}



void PyModuleLoader::DeleteWrapper_(unsigned long id)
{
    DeleteObject_(id);
}



void PyModuleLoader::AddPyModule(const std::string & key,
                                 boost::python::object func, const modulestore::ModuleInfo & minfo)
{

    ModuleStore::ModuleGeneratorFunc cfunc = std::bind(&PyModuleLoader::CreateWrapper_, this, func,
                                                       std::placeholders::_1,
                                                       std::placeholders::_2,
                                                       std::placeholders::_3);

    ModuleStore::ModuleRemoverFunc dfunc = std::bind(&PyModuleLoader::DeleteWrapper_, this, std::placeholders::_1);
    mst_->AddModule(key, cfunc, dfunc, minfo);
}



void PyModuleLoader::DeleteObject_(unsigned long id)
{
    objects_.erase(id);
}



void PyModuleLoader::UnloadAll(void)
{
    objects_.clear();
}


namespace export_python {

// wraps PyModuleLoader::AddPyModule so that it can take a dict for the modulestore::ModuleInfo
void Wrap_PyModuleLoader_AddPyModule(PyModuleLoader * ml,
                                     const std::string & key, boost::python::object func,
                                     const boost::python::dict & minfo)
{
    // dictionary is converted to modulestore::ModuleInfo via constructor
    return ml->AddPyModule(key, func, minfo);
}

} // close namespace export_python


} // close namespace modulestore
} // close namespace bpmodule
