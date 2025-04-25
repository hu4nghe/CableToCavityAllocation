/**
 * @file py_binding.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * This file creates binding functions of cable_allocator class for python call.
 * @version 1.4
 * @date 2025-04-25
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "cable_allocator.h"

namespace py = pybind11;

PYBIND11_MODULE(cable_allocator_pybind11, m) 
{
    m.doc() = "Python bindings for the cable_allocator class";

    // Bind the cable_allocator class
    py::class_<cable_allocator>(m, "CableAllocator")
        .def(py::init<const std::vector<std::tuple<int, int, double, double>>&>(),
             "Constructor that takes cavity data as a list of tuples (cavity_id, component_id, x, y)")
        
        .def("add_cable", &cable_allocator::add_cable,
             "Adds a new cable ",
             py::arg("wires"), py::arg("mode"))
             
        .def("get_cable_allocations", &cable_allocator::get_cable_allocations,
             "Gets possible allocations for a cable",
             py::arg("cable_ID"))
             
        .def("confirme_allocation", &cable_allocator::confirme_allocation,
             "Confirms a specific allocation for a cable",
             py::arg("cable_ID"), py::arg("allocation_idx"))
             
        .def("print_connector_status", &cable_allocator::get_connector_status,
             "Get the current status of the connector");
}