/**
 * @file cable_allocation.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief A set of possible connections for a cable.
 * @version 1.3
 * @date 2025-04-22
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_component_base.h"
#include "connector.h"

class cable_allocation
{
private:

    std::unordered_map<int, int> _wire_layout;
    double                       _score;
    std::weak_ptr<connector>     _wp_connector;

public:

    cable_allocation(const std::vector<std::pair<int,int>>& connections, 
                           std::shared_ptr<connector>       connector);

    auto get_layout() const{ return _wire_layout; }
    auto get_score() const { return _score; }
};