/**
 * @file cable_allocation.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * A set of possible connections for a cable.
 * @version 1.4
 * @date 2025-04-25
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#pragma once

#include "electronic_component.h"
#include "connector.h"

#include <set>

class cable_allocation
{
private :

    std::set<int>      _reserved_cavities;
    double             _score;

public :

    /**
     * @brief 
     * Construct a new cable allocation object
     * 
     * @param connections A set that includes the cavities allocated to the cable.
     * @param connector A pointer that points to the cable's target connector.
     * 
     * @throw std::runtime_error If connector pointer is expired.
     */
    cable_allocation(const std::vector<int>&           connections, 
                           std::shared_ptr<connector>  connector);

    /**
     * @brief 
     * Operator< for std::set & std::map.
     * 
     * @param other Another cable_allocation object.
     * @return true If reserved_cavities < other's, if equal, compare their score.
     * @return false If they have same reserved cavities.
     */
    bool operator<(const cable_allocation& other) const noexcept;

    /**
     * @brief Get the set of allocated cavityies.
     * 
     * @return std::set<int> Allocated cavities for current cable.
     */
    const auto& get_layout() const{ return _reserved_cavities; }

    /**
     * @brief Get current allocation's score.
     * 
     * @return double Current allocation's score.
     */
    const double get_score() const { return _score; }
};