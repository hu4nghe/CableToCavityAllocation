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
    // Instantiate a void component is NOT allowed.
    electronic_component_base() = delete;

    /**
     * @brief Base class constructor for components.
     * 
     * @param id Component's ID.
     * @param gauge Component's size in American Wire Gauge.
     */
    electronic_component_base(const int& id, const int& gauge);

   

    // Getters
    const AWG get_gauge() const { return _gauge; }
    const int get_ID()    const { return _ID; }
};
