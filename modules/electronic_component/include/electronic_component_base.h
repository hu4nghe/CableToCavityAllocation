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

class electronic_component_base 
{
protected:
    const int _ID;
    const AWG _gauge;
    
public:

    /// Constructors ///

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
    electronic_component_base(const int& id, 
                              const int& gauge);

    /**
     * @brief Base copy constructor.
     * 
     * @param other Another electronic_component_base object to copy
     */
    electronic_component_base(const electronic_component_base& other);

    /**
     * @brief Base move constructor
     * 
     * @param other Another electronic_component_base object to move.
     */
    explicit electronic_component_base(electronic_component_base&& other);

    bool operator<(const electronic_component_base& other) const; 
    

    // Getters
    const AWG get_gauge() const { return _gauge; }
    const int get_ID()    const { return _ID; }

    /**
     * @brief Check if two component can fit each other
     *        (May add contact calculation in future.)
     * 
     * @param other Another electronic_component_base object.
     * @return true If two components have the same gauge
     * @return false If two components have differents gauges.
     */
    bool is_compatible(const electronic_component_base& other) const; 
};
