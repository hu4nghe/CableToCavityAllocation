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

    std::vector<cable_allocation> _allocations;
    std::weak_ptr<connector>  _wp_connector;

public:

    cable(std::shared_ptr<connector> _sp_connector) : 
        _wp_connector(_sp_connector) {}
    
    bool generate_allocations();
    void add_wires(const std::vector<std::tuple<int, int>>& wires);

    /// Getters
    auto size()   const { return _container.size(); }
    auto get_allocations() const { return _allocations; }
};