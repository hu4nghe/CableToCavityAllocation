/**
 * @file cable_allocator.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Header for allocator who manages connectors, cables and their connections.
 * @version 1.4
 * @date 2025-04-25
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */

#pragma once

#include "electronic_container.h"
#include "electronic_component.h"

#include <ranges>

class cable_allocator
{ 
private :

    std::vector<cable>         _cable_list;
    std::shared_ptr<connector> _sp_connector;
    
public : 
    /**
     * @brief 
     * Construct a new cable_allocator object.
     * 
     * @param cavity_data Cavity data to initialize the connector, in format <ID, gauge, Pos_x, Pos_y>.
     */
    cable_allocator(const std::vector<std::tuple<int, int, double, double>>& cavity_data);

     /**
     * @brief 
     * Adds a new cable to the region pool and generate possible allocations.
     * 
     * @param wires A vector of tuples representing the wires and their gauges.
     * @param mode 1 to select allocations adjacent to placed cables. Others to select all allocations.
     * @return true If the cable was successfully added, false otherwise.
     */
    bool add_cable(const std::vector<std::tuple<int, int>>& wires, int mode);
    
    /**
     * @brief 
     * Return a vector of allocations. 
     * Each allocation contains a score and a occupied cavity ID list.
     *
     * @param cable_ID The cable ID to which the allocations belong.
     * @return A vector of allocations
     */
    auto get_cable_allocations(int cable_ID) const
    {
        return _cable_list.at(cable_ID - 1).get_allocations()
            | std::views::transform([](const auto& a){return std::tuple{a.get_score(), a.get_layout()};}) 
            | std::ranges::to<std::set>();
    }

    /**
     * @brief 
     * Get the current connector status
     * 
     * @return A vector, the nth is m means the nth cavity is allocated to cable m, 0 if cavity is available.
     */
    auto get_connector_status() const{ return _sp_connector->get_status(); }
    
    /**
     * @brief 
     * To confirme a allocation of a cable.
     * 
     * @param cable_ID The cable that we want to allocate.
     * @param allocation_idx The allocation's index.
     */
    void confirme_allocation(int cable_ID, int allocation_idx)
    { 
        _cable_list.at(cable_ID - 1 ).confirme_allocation(cable_ID, allocation_idx); 
    }

    /**
     * @brief
     * Debug fonctions to print the status of connector's cavities .
     * 
     */
    void print_connector_status() const 
    { 
        _sp_connector->print_current_connector_status(); 
    }

};
