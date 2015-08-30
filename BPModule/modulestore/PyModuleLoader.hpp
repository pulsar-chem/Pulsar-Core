#ifndef PYMODULELOADER_H
#define PYMODULELOADER_H

#include <memory>
#include <unordered_map>
#include <string>

#include <boost/python.hpp>


//forward declarations
namespace bpmodule {

namespace modulebase {
class ModuleBase;
}

namespace modulestore {
class ModuleStore;
class ModuleInfo;
}
}
// end forward declarations




namespace bpmodule {
namespace modulestore {

class PyModuleLoader
{
    public:

        PyModuleLoader(modulestore::ModuleStore * mst);
        ~PyModuleLoader();

        PyModuleLoader & operator=(const PyModuleLoader & rhs) = delete;
        PyModuleLoader(const PyModuleLoader & rhs) = delete;

        void AddPyModule(const std::string & key, boost::python::object func, const modulestore::ModuleInfo & minfo);

        void UnloadAll(void);

    private:
        typedef std::unordered_map<unsigned long, boost::python::object> ObjectMap;

        modulestore::ModuleStore * mst_;
        ObjectMap objects_;

        void DeleteObject_(unsigned long id);

        modulebase::ModuleBase * CreateWrapper_(boost::python::object fn, const std::string & key, unsigned long id, const modulestore::ModuleInfo & options);
        void DeleteWrapper_(unsigned long id);
};


namespace export_python {

void Wrap_PyModuleLoader_AddPyModule(PyModuleLoader * ml,
                                     const std::string & key, boost::python::object func,
                                     const boost::python::dict & minfo);

} // close namespace export_python

} // close namespace modulestore
} // close namespace bpmodule


#endif
