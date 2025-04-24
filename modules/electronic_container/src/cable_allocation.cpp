/**
 * @file cable_allocation.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocation class.
 * @version 1.3
 * @date 2025-04-22
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "cable_allocation.h"
#include "min_enclosing_circle.h"

#include <ranges>

cable_allocation::cable_allocation(const std::set<int>&             connections,
                                         std::shared_ptr<connector> sp_connector) :
    _reserved_cavities( connections),
    _score (0.0)
{
    std::vector<std::pair<double,double>> coords;
    for(const auto& connected_cavity : connections)
        coords.push_back(sp_connector->get_component(connected_cavity)->get_pos());
    _score = geo_tools::calculate_min_enclosing_circle_radius(coords);
}

bool cable_allocation::operator<(const cable_allocation &other) const
{
    if (_reserved_cavities == other._reserved_cavities) 
        return false;
    
    if (_score == other._score) 
        return _reserved_cavities < other._reserved_cavities; 
    
    return _score < other._score; 
}
