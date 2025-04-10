/**
 * @file electronic_component_base.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief Electronic components(wire and cavity) base class
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#pragma once

#include <memory>
#include <type_traits>



class electronic_component_base;

template <typename T>
concept electronic_component_type = 
    std::is_base_of_v<electronic_component_base,T>;

template <electronic_component_type T>
using p_component = std::shared_ptr<T>;

// Americal wire gauge enum
enum class AWG
{
    AWGUnkown = -1,
    
    AWG8  = 8,
    AWG10 = 10,
    AWG12 = 12,
    AWG16 = 16,
    AWG20 = 20, 
    AWG22 = 22
};

class electronic_component_base: public std::enable_shared_from_this<electronic_component_base>
{
protected:

    const int _ID;
    const AWG _gauge;

public:

    /**
     * @brief Default constructor set attributs to unknwon status.
     */
    electronic_component_base();

    /**
     * @brief Base class constructor.
     * 
     * @param id Component's ID.
     * @param gauge Component's size in American Wire Gauge.
     */
    electronic_component_base(const int& ID, const int& gauge);

    /**
     * All component is unique, identified with ID.
     * You can NEVER copy a component.
     */
    electronic_component_base(const electronic_component_base& other) = delete;
    electronic_component_base& operator=(const electronic_component_base& other) = delete;

    /**
     * @brief Base move constructor.
     * 
     * @param other Another electronic_component_base object to move.
     */
    explicit electronic_component_base(electronic_component_base&& other);
    
    /**
     * @brief Overrided operator< for std::set/std::map
     * 
     * @param other Another electronic component
     * @return true if current object's ID is inferior than the other's.
     * @return false if if current object's ID is superior than the other's.
     */
    bool operator<(const electronic_component_base& other) const; 

    /**
     * @brief Get the ID of the component.
     * 
     * @return int ID of the component.
     */
    const AWG get_gauge() const;

    /**
     * @brief Get the ID of the component.
     * 
     * @return int ID of the component.
     */
    const int get_ID() const;

    /**
     * @brief Check if two component can fit each other.
     *        (May add contact calculation in future.)
     * 
     * @param other Another electronic_component_base object.
     * @return true if two components have the same gauge.
     * @return false if two components have differents gauges.
     */
    bool is_compatible(const electronic_component_base& other) const; 
};
