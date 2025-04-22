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

cable_allocation::cable_allocation(const std::vector<std::pair<int, int>>& connections,
                                         std::shared_ptr<connector>        sp_connector) :
    _wire_layout(std::map<int, int>(connections.begin(),connections.end())),
    _score (0.0)
{
    std::vector<std::pair<double,double>> coords;
    for(const auto& [_, connected_cavity] : connections)
        coords.push_back(sp_connector->get_component(connected_cavity)->get_pos());
    _score = geo_tools::calculate_min_enclosing_circle_radius(coords);
}