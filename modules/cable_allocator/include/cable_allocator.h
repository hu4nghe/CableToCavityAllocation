/**
 * @file cable_allocator.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Header for allocator who manages connectors, cables and their connections.
 * @version 2.0
 * @date 2025-07-09
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */

#pragma once

#include "electronic_container.h"
#include "electronic_component.h"

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
    cable_allocator(const std::vector<std::tuple<int, int, double, double>>& cavity_data) : 
        _sp_connector(std::make_shared<connector>(cavity_data)) {}

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
     * @return A vector of allocations in tuple format :
     *         - double : Allocation's score
     *         - std::set<int> : Indices of cavities allocated.
     * 
     * @throw std::out_of_range If cable_ID is not valid.
     */
    auto get_cable_allocations(int cable_ID) -> std::set<std::tuple<double, std::set<int>>> const;
    
    /**
     * @brief 
     * To confirme a allocation of a cable.
     * 
     * @param cable_ID The cable that we want to allocate.
     * @param allocation_idx The allocation's index.
     * 
     * @throw std::out_of_range If cable_ID is not valid.
     */
    void confirme_allocation(int cable_ID, int allocation_idx);

    /**
     * @brief 
     * Get the current connector status
     * 
     * @return A vector<int>, vec[n] is equal to
     *         - 0 if cavity is available.
     *         - m if cavity is occupied by cable m.
     */
    auto get_connector_status() -> std::vector<int> const;    
};