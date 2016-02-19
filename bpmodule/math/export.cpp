/*! \file
 *
 * \brief Python exports for math
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#include "bpmodule/python/Pybind11.hpp"
#include "bpmodule/python/Pybind11_stl.hpp"
#include "bpmodule/python/Pybind11_functional.hpp"
#include "bpmodule/math/Factorial.hpp"
#include "bpmodule/math/Universe.hpp"
#include "bpmodule/math/MathSet.hpp"
#include "bpmodule/math/Point.hpp"

PYBIND11_DECLARE_HOLDER_TYPE(T,std::shared_ptr<T>);

//! \todo Export exact casts? Or have the equivalent with python?

namespace bpmodule {
namespace math {
typedef Universe<std::string> PyU_t;
typedef MathSet<std::string> PySet_t;

namespace export_python {


    
    
PYBIND11_PLUGIN(math)
{
    pybind11::module m("math", "Some common math operations");

    m.def("Factorial", Factorial); 
    m.def("FactorialF", FactorialF); 
    m.def("FactorialD", FactorialD); 

    m.def("DoubleFactorial", DoubleFactorial); 
    m.def("DoubleFactorialF", DoubleFactorialF); 
    m.def("DoubleFactorialD", DoubleFactorialD); 

    m.def("Double2nm1Factorial", Double2nm1Factorial); 
    m.def("Double2nm1FactorialF", Double2nm1FactorialF); 
    m.def("Double2nm1FactorialD", Double2nm1FactorialD);
    
   pybind11::class_<PyU_t,std::shared_ptr<PyU_t>>(m,"Universe")
    .def(pybind11::init<>())
    .def("append",&PyU_t::operator<<,"Adds a new universe to the set")
    .def("__iadd__",&PyU_t::operator+=,"Makes this the union of this and other")
    .def("__isub__",&PyU_t::operator-=,
         "Makes this the set difference of this and other")
    .def("__idiv__",&PyU_t::operator/=,
         "Makes this the intersection of this and other")
    .def("__add__",&PyU_t::operator+,"Returns union of this and other")
    .def("__sub__",&PyU_t::operator-,"Returns set-difference of this and other")
    .def("__div__",&PyU_t::operator/,
         "Returns the intersection of this and other")
    .def("__str__",&PyU_t::ToString,"Prints out the universe");

    pybind11::class_<PySet_t>(m,"MathSet")
    .def(pybind11::init<std::shared_ptr<PyU_t>>())
    .def(pybind11::init<const PySet_t &>())
    .def("append",(PySet_t& (PySet_t::*)(const std::string&)) 
                  &PySet_t::operator<<,"Adds a new string to the set")
    .def("append",(PySet_t& (PySet_t::*)(size_t)) 
                  &PySet_t::operator<<,"Adds a new string to the set")
    .def("Transform", &PySet_t::Transform,
                     "Perform a transformation on the elements of the set")
    .def("__iadd__",&PySet_t::operator+=,
         "Makes this the union of this and other")
    .def("__isub__",&PySet_t::operator-=,
         "Makes this the set difference of this and other")
    .def("__idiv__",&PySet_t::operator/=,
         "Makes this the intersection of this and other")
    .def("__add__",&PySet_t::operator+,"Returns union of this and other")
    .def("__sub__",&PySet_t::operator-,
         "Returns set-difference of this and other")
    .def("__div__",&PySet_t::operator/,
         "Returns the intersection of this and other")
    .def("Complement",&PySet_t::Complement,"Returns the complement of this")
    .def("__str__",&PySet_t::ToString,"Prints out the set");
    


    pybind11::class_<Point>(m, "Point")
    .def("GetCoords", &Point::GetCoords)
    .def("SetCoords", static_cast<void (Point::*)(double, double, double)>(&Point::SetCoords))
    .def("SetCoords", static_cast<void (Point::*)(const Point::CoordType &)>(&Point::SetCoords))
    ;
    


    return m.ptr();
}


} // close namespace export_python
} // close namespace math 
} // close namespace bpmodule

