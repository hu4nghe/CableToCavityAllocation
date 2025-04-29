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
#include "cable_allocator.h"

namespace py = pybind11;

PYBIND11_MODULE(cable_allocator_py, m) {
    py::class_<cable_allocator>(m, "cable_allocator")
        .def(py::init<const std::vector<std::tuple<int, int, double, double>>&>())
        .def("add_cable", &cable_allocator::add_cable)
        .def("get_connector_status", &cable_allocator::get_connector_status);
}
