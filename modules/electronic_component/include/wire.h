/**
 * @file wire.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent wires to connect.
 * @version 1.2
 * @date 2025-04-17
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_component_base.h"

class wire : public electronic_component_base
{
public:
    wire(int ID, int wire_gauge) :
        electronic_component_base(ID, wire_gauge) {}
};
