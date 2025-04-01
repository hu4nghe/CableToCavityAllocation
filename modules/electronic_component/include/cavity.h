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
     * @brief Compare gauge to other cavity.
     * 
     * @param other Another cavity object.
     * @return true if two cavity have the same gauge.
     * @return false if two cavity have differents gauges.
     */
    bool operator==(const cavity& other) const;

    bool operator<(const cavity& other) const;

    /**
     * @brief Calculate distance between two cavities on the same connector.
     * 
     * @param other Another cavity object.
     * @return Distance between two cavity, +∞ if send itself as argument.
     */
    double distance(const cavity& other) const;

    /**
     * @brief check if a wire is compatible to the cavity.
     * 
     * @param wire The wire to check.
     * @return true if the wire and the cavity have the same gauge.
     * @return false if the wire and the cavity have differents gauges.
     */
    bool is_compatible(const wire& wire) const;
};
