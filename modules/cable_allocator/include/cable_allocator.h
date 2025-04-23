/**
 * @file cable_allocator.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Allocator who manages cable connections.
 * @version 1.3
 * @date 2025-04-22
 * 
 * @copyright 
 * Dassault Systemes 2025
 */
#pragma once

#include "electronic_container.h"
#include "electronic_component.h"
#include <map>

class cable_allocator
{
private:

    std::vector<cable>         _cable_list;
    std::shared_ptr<connector> _sp_connector;
    
public : 
    /**
     * @brief Construct a new cable allocator object.
     * 
     * @param connector The connector object containing cavities and their connections.
     */
    cable_allocator(const std::vector<std::tuple<int, int, double, double>>& cavity_data);

     /**
     * @brief Adds a new cable to the region pool.
     * 
     * @param cable_ID The ID of the cable to be added.
     * @param wires A vector of tuples representing the wires and their gauges.
     * @return true if the cable was successfully added, false otherwise.
     */
    bool add_cable(const std::vector<std::tuple<int, int>>& wires);
    
    auto get_allocations(int cable_ID) const -> std::vector<cable_allocation>;

};