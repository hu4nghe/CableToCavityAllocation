/**
 * @file electronic_component_base.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Electronic components(wire and cavity) base class
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include <functional>
#include <memory>
#include <type_traits>

#include "AWG.h"

class electronic_component_base;

/**
 * @brief electronic component type concept
 * 
 * @tparam T Type to check
 */
template <typename T>
concept electronic_component_type = 
    std::is_base_of_v<electronic_component_base,T>;
template <electronic_component_type T>
using sp_component = std::shared_ptr<T>;


class electronic_component_base
{
protected:

    const int _ID;
    const AWG _gauge;

public:

    electronic_component_base() :
        _ID(0),
        _gauge(AWG::AWGUnkown){}

    /**
     * @brief 
     * Base class constructor.
     * 
     * @param id Component's ID.
     * @param gauge Component's size in American Wire Gauge.
     */
    electronic_component_base(const int& ID, 
                              const int& gauge) : 
        _ID(ID),
        _gauge(static_cast<AWG>(gauge)){}

    /**
     * All component is unique, identified with ID.
     * You do not want to copy a component.
     */
    electronic_component_base           (const electronic_component_base& other) = delete;
    electronic_component_base& operator=(const electronic_component_base& other) = delete;

    /**
     * @brief 
     * Base move constructor.
     * 
     * @param other Another electronic_component_base object to move.
     */
    explicit electronic_component_base(electronic_component_base&& other) : 
        _ID(std::move(other._ID)),
        _gauge(std::move(other._gauge)){}
    
    /**
     * @brief 
     * Overrided operator< for std::set/std::map
     * 
     * @param other Another electronic component
     * @return true if current object's ID is inferior than the other's.
     * @return false if if current object's ID is superior than the other's.
     */
    bool operator<(const electronic_component_base& other) const { return _ID < other._ID; }
    /**
     * @brief 
     * Overrided operator== for STL unordered container
     * 
     * @param other Another electronic component
     * @return true if current object's ID is equal to the other's.
     * @return false if if current object's ID is different from the other's.
     */
    bool operator==(const electronic_component_base& other) const { return _ID == other._ID; }

    /**
     * @brief 
     * Check if two component can fit each other.
     * (May add contact calculation in future.)
     * 
     * @param other Another electronic_component_base object.
     * @return true if two components have the same gauge.
     * @return false if two components have differents gauges.
     */
    bool is_compatible(const electronic_component_base& other) const { return _gauge == other._gauge; }

    /// Getters
    const AWG get_gauge() const { return _gauge; }
    const int get_ID()    const { return _ID; }
};

/// Hash function for electronic_component_base for STL unordered container
namespace std 
{
    template<>
    struct hash<electronic_component_base> 
    {
        size_t operator()(const electronic_component_base& comp) const 
        {
            return std::hash<int>()(comp.get_ID());
        }
    };
}