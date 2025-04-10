/**
 * @file wire.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the wire class
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "wire.h"

wire::wire(int ID, int wire_gauge) :
    electronic_component_base(std::move(ID), std::move(wire_gauge)){}
