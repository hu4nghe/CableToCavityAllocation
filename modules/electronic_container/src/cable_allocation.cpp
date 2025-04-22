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

#include <ranges>

cable_allocation::cable_allocation(const std::vector<std::pair<int, int>>& connections,
                                 std::shared_ptr<connector> sp_connector) :
    _wp_connector(sp_connector),
    _wire_layout(std::unordered_map<int, int>(connections.begin(),connections.end())),
    _score (0.0)
{
    
    if(auto promoted_connector_ptr = _wp_connector.lock())
        ;

    else 
        throw std::runtime_error("cable_allocation : connector is not available");

}