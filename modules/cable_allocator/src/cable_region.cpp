/**
 * @file cable_region.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_region class.
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "cable_region.h"

#include <ranges>

cable_region::cable_region( const std::vector<std::pair<int, int>>& connections) :
    _wire_layout(std::map<int, int>(connections.begin(),connections.end())){}

bool cable_region::operator<(const cable_region &other) const
{
    return _wire_layout < other._wire_layout; 
}

bool cable_region::has_unavailable_cavity(const std::set<int>& unavailable_pool) const 
{
    for(const auto& cavity_index : std::views::values(_wire_layout))
        if(unavailable_pool.count(cavity_index)) 
            return true;
    return false;
}

std::map<int, int> cable_region::get_layout() const
{ 
    return _wire_layout; 
}