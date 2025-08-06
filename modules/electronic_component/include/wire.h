/**
 * @file wire.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent wires to connect.
 * @version 2.0
 * @date 2025-07-09
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#pragma once

#include "electronic_component_base.h"

#include <concepts>

class wire : public electronic_component_base
{

public :

    /**
     * @brief 
     * Construct a new wire object.
     * 
     * @param ID Wire's ID.
     * @param wire_gauge Wire's size in AWG.
     */
    wire(int ID, int wire_gauge) :
        electronic_component_base(ID, wire_gauge) {}
};

template <typename T>
concept is_wire_component = std::is_same_v<T, wire>;
