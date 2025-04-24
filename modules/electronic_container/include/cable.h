/**
 * @file cable.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a cable, who includes multiples wires
 * @version 1.3
 * @date 2025-04-22
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_container_base.h"
#include "connector.h"
#include "cable_allocation.h"

class cable : public electronic_container_base<wire>
{
private: 

    std::set<cable_allocation>    _allocations;
    std::weak_ptr<connector>      _wp_connector;
    bool                          _is_allocated;

public:

    cable(std::shared_ptr<connector> _sp_connector) : 
        _wp_connector(_sp_connector),
        _is_allocated(false) {}
    
    bool generate_allocations(int searching_range);



    void add_wires(const std::vector<std::tuple<int, int>>& wires);

    /// Getters
    auto size() const { return _container.size(); }
    auto get_allocations() const { return _allocations; }
    auto is_allocated() const { return _is_allocated; }
    void confirme_allocation(int current_cable_ID, int allocation_ID);
};