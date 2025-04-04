/**
 * @file cable_allocator_py_module.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * @version 1.0
 * @date 2025-04-04
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#include "cable_allocator.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"


struct py_input
{
    int _ID;
    std::pair<double,double> _position;
    int _size;

    py_input(const int&    id, 
             const double& pos_x, 
             const double& pos_y, 
             const int&    size);
};