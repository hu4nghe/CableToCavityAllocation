/**
 * @file electronic_container_base.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief Electronic containers(cable and connector) base class
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_component.h"

#include <map>
#include <vector>

class cable_allocator;

template <electronic_component_type T>
class electronic_container_base
{
protected:
    std::map<AWG, std::vector<p_component<T>>> _container;

public:
    friend class cable_allocator;
    // Instantiate a void container is NOT allowed.
    electronic_container_base() = delete;
    /**
     * @brief Construct a new electronic container base object
     * 
     * @param components A vector contains all components. 
     *                   The constructor will automatically classifie these component by their gauge.
     */
    electronic_container_base(const std::vector<T>& components)
    {
        for(auto& p : components)
            _container[p.get_gauge()].push_back(std::make_shared<T>(p));
    }
};