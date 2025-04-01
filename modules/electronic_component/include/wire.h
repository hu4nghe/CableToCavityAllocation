/**
 * @file wire.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief The class that represent wires to connect.
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Dassault Systemes 2025
 * 
 */

#pragma once

#include "electronic_component_base.h"

class wire : public electronic_component_base
{
public:
    /**
     * @brief Construct a new wire object
     * 
     * @param id wire's id
     * @param wire_gauge wire's size in American Wire Gauge.
     */
    wire(const int& id, 
         const int& wire_gauge);
};
