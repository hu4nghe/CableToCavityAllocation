/**
 * @file cable_region.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief A set of possible connections for a cable.
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_component.h"
#include "electronic_container.h"

#include <map>
#include <set>

class cable_region
{
private:

    std::map<int, int>       _wire_layout;
    double                   _score;
    std::weak_ptr<connector> _connector;

public:

    /**
     * @brief Construct a new cable region object
     * 
     * @param cable_ID ID of the cable.
     * @param connections A vector of pairs representing wire-cavity connections.
     */
    cable_region(const std::vector<std::pair<int,int>>& connections);
    bool operator<(const cable_region& other) const { return _wire_layout < other._wire_layout; }
    auto get_layout() const{ return _wire_layout; }
    auto get_score() const { return _score; }
};