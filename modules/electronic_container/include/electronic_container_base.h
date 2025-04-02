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

template <electronic_component_type T>
class electronic_container_base
{
protected:
    std::map<AWG, std::vector<p_component<T>>> _container;

public:
    // Instantiate a void container is NOT allowed.
    electronic_container_base() = delete;
    electronic_container_base(const std::vector<T>& components)
    {
        for(auto& p : components)
            _container[p.get_gauge()].push_back(std::make_shared<T>(p));
    }

};