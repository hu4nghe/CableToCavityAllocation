/**
 * @file cable_allocation.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocation class.
 * @version 2.0
 * @date 2025-07-09
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#include "cable_allocation.h"
#include "min_enclosing_circle.h"

#include <cmath>
#include <stdexcept>

cable_allocation::cable_allocation(const std::vector<int>&          connections,
                                         std::shared_ptr<connector> sp_connector) :
    _reserved_cavities(connections.begin(),connections.end()),
    _score (0.0)
{
    if (!sp_connector) throw std::runtime_error("connector is not valid.");
    std::vector<std::pair<double,double>> coords;
    for (const auto& connected_cavity : connections)
        coords.push_back(sp_connector->get_component(connected_cavity)->get_pos());
    _score = std::ceil(geo_tools::calculate_min_enclosing_circle_radius(coords));
}

bool cable_allocation::operator<(const cable_allocation &other) const noexcept
{
    if (_reserved_cavities == other._reserved_cavities) 
        return false;
    
    if (_score == other._score) 
        return _reserved_cavities < other._reserved_cavities; 
    
    return _score < other._score; 
}