/**
 * @file cavity.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent cavities on connector
 * @version 1.2
 * @date 2025-04-17
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_component_base.h"
#include <utility>// for std::pair

class cavity : public electronic_component_base
{
private:

    const std::pair<double,double> _position;

public:
    
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
        _position(x, y){}

    cavity(cavity&& other) :    
        electronic_component_base(std::move(other)),
        _position(other._position){}
    
    /**
     * @brief 
     * Compare gauge to other cavity.
     * 
     * @param other Another cavity object.
     * @return true if two cavity have the same gauge.
     * @return false if two cavity have differents gauges.
     */
    bool has_the_same_gauge(const cavity& other) const { return _gauge == other._gauge; }
    
    /**
     * @brief 
     * Calculate distance between current cavity and another point.
     * 
     * @param other Another cavity object.
     * @return double Distance between two cavity, +∞ if send itself as argument.
     */
    double distance(const std::pair<double,double>& point) const;
    // shortcut for cavity object.
    double distance(const cavity& other) const { return distance(other._position); }
     
    /**
     * @brief 
     * Calculate the midpoint between two cavities.
     * 
     * @param other Another cavity object.
     * @return std::pair<double,double> Midpoint between two cavities.
     */
    std::pair<double,double> midpoint(const cavity& other) const;
};
