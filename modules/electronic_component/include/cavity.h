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
#include "wire.h"

#include <utility>

class cavity : public electronic_component_base
{
private:

    const std::pair<double,double> _position;
    std::weak_ptr<wire>            _connected_wire;

public:

    /// Constructors///

    /**
    * @brief Construct a new cavity::cavity object.
    * 
    * @param id Cavity ID on the connector.
    * @param cavity_gauge American Wire Gauge.
    * @param x x coordinate.
    * @param y y coordinate.
    */
    cavity(const int&    id,
           const int&    cavity_gauge, 
           const double& x,
           const double& y);

    /**
     * @brief Move constructor for initialization
     * 
     * @param other cavity object to move
     */
    cavity(cavity&& other);
    
    /// Operators ///
    
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

    /// tools ///

    /**
     * @brief Calculate distance between two cavities on the same connector.
     * 
     * @param other Another cavity object.
     * @return Distance between two cavity, +∞ if send itself as argument.
     */
    double distance(const cavity& other) const;

    /**
     * @brief Connect with a wire.
     * 
     * @param target_wire a shared_ptr to target wire.
     */
    void connect(p_component<wire> target_wire);

    /**
     * @brief Disconnect 
     * 
     */
    void disconnect();

    /**
     * @brief Returns availability of current component.
     * 
     * @return true if component is available.
     * @return false if component is unavailable.
     */
    bool is_available() const;
    auto get_wire() const { return _connected_wire.lock(); }
};
