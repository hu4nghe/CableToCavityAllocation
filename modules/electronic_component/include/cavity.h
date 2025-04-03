/**
 * @file cavity.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief The class that represent cavities on connector
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_component_base.h"

#include <utility>

class wire;

class cavity : public electronic_component_base
{
private:
    const std::pair<double,double> _position;
    bool                           _availability;

public:

    /// Constructors///

    /**
    * @brief Construct a new cavity::cavity object.
    * 
    * @param id Cavity ID on the connector.
    * @param cavity_gauge American Wire Gauge.
    * @param x x coordinate.
    * @param y y coordinate.
    * @param is_available Cavity's avaibility.
    */
    cavity(const int&    id,
           const int&    cavity_gauge, 
           const double& x,
           const double& y , 
           const bool&   is_available);
    
    /**
     * @brief Copy constructor for building adjacency list
     * 
     * @param other cavity object to copy
     */
    cavity(const cavity& other);

    /**
     * @brief Move constructor for initialization
     * 
     * @param other cavity object to move
     */
    explicit cavity(cavity&& other);
    
    ///Comparison operators for STL containers///
    
    /**
     * @brief Compare gauge to other cavity.
     * 
     * @param other Another cavity object.
     * @return true if two cavity have the same gauge.
     * @return false if two cavity have differents gauges.
     */
    bool operator==(const cavity& other) const;

    /**
     * @brief Compare ID of two cavities
     *        (Only for STL container use, do not call explicitly)
     * 
     * @param other Another cavity object.
     * @return true if current cavity ID is smaller than other's.
     * @return false if current cavity ID is bigger than other's.
     */
    bool operator<(const cavity& other) const;

    /// Useful tools ///

    /**
     * @brief Calculate distance between two cavities on the same connector.
     * 
     * @param other Another cavity object.
     * @return Distance between two cavity, +∞ if send itself as argument.
     */
    double distance(const cavity& other) const;

    bool is_available() const { return _availability; }
    void set_availability(const bool& new_status) { _availability = new_status; }

};
