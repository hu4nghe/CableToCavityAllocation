#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "cable_allocator.h"

namespace py = pybind11;

PYBIND11_MODULE(cable_allocator_pybind11, m) 
{
    m.doc() = "Python bindings for the cable_allocator class";

    py::class_<cable_allocator>(m, "CableAllocator")
      
        .def(py::init<const std::vector<std::tuple<int, int, double, double>>&>(), 
             py::arg("cavities"), 
             "Constructor for CableAllocator")

        
        .def("connect", &cable_allocator::connect, 
             py::arg("connections"), 
             "Connect cables using a map of connections")

       
        .def("add_cable", &cable_allocator::add_cable, 
             py::arg("cable_ID"), py::arg("wires"), 
             "Add a cable with a given ID and wires, returning a vector of tuples");
}