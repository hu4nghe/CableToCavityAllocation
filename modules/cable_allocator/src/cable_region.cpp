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

cable_region::cable_region(const std::vector<std::pair<int, int>>& connections) :
    _wire_layout(std::map<int, int>(connections.begin(),connections.end())),
    _score (0.0)
{
    auto promoted_connector_ptr = _connector.lock();
    if(!promoted_connector_ptr)
        throw std::runtime_error("cable_region : connector is not available");

    for(const auto& [_, i] : _wire_layout)
        for(const auto& [_, j] : _wire_layout)
            _score = std::max(_score, promoted_connector_ptr->distance(i, j));
}