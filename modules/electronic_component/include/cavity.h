/**
 * @file cavity.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent cavities on connector
 * @version 1.4
 * @date 2025-04-25
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#pragma once

#include "electronic_component_base.h"

#include <cmath>

class cavity : public electronic_component_base
{
private :

    const std::pair<double,double> _position;
    int                            _cable_ID;

public :
    
    /**
    * @brief 
    * Construct a new cavity object.
    * 
    * @param ID Cavity ID on the connector.
    * @param cavity_gauge American Wire Gauge.
    * @param x x coordinate.
    * @param y y coordinate.
    */
    cavity(int ID, 
           int cavity_gauge, 
           double x, 
           double y) :
        electronic_component_base(ID, cavity_gauge),
        _position(x, y),
        _cable_ID(0) {}

    /**
     * @brief Move constructor
     * 
     * @param other Cavity object to move.
     */
    cavity(cavity&& other) :    
        electronic_component_base(std::move(other)),
        _position(std::move(other._position)),
        _cable_ID(std::exchange(other._cable_ID, 0)) {}
    
    /**
     * @brief
     * Allocate the cavity to a cable.
     * @param cable_ID The ID of the cable to allocate.
     */
    void allocate_to_cable(int cable_ID) { _cable_ID = cable_ID; }

    /**
     * @brief
     * Check if the cavity is available.
     * @return 0 if the cavity is available.
     * @return cable_ID if the cavity is occupied by a cable.
     */
    int status() const { return _cable_ID; }

    /**
     * @brief 
     * Calculate distance between current cavity and another point.
     * 
     * @param other Another cavity object.
     * @return double Distance between two cavity, +∞ if send itself as argument.
     */
    double distance(const std::pair<double,double>& point) const
    {
        return std::hypot(point.first  - _position.first, 
                          point.second - _position.second);
    }

    /**
     * @brief 
     * Alias to calculate the distance between two cavities.
     * 
     * @param other Another cavity.
     * @return double Distance between current cavity and other.
     */
    double distance(const cavity& other) const { return distance(other._position); }
    
    /**
     * @brief 
     * Get the cavity's coordinate on the connector.
     * 
     * @return std::pair<doube, doube> The 2D coordinate pair (x, y). 
     */
    const auto& get_pos() const { return _position; }
};
