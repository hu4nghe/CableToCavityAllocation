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

#include <vector>

class cable_allocator;

template <electronic_component_type T>
class electronic_container_base
{
protected:

    std::vector<p_component<T>> _components;

public:
    friend class cable_allocator;

    // Instantiate a void container is NOT allowed.
    electronic_container_base() = delete;

    /**
     * @brief Construct a new electronic container base object
     * 
     * @param components A vector containing all components. 
     */
    electronic_container_base(std::vector<T>&& components)
    {
        for (auto& p : components)
            _components.push_back(std::make_shared<T>(std::move(p)));
    }

    /**
     * @brief Get a component by its ID.
     * 
     * @param ID The ID of the component to retrieve.
     * @return A shared pointer to the component, or nullptr if not found.
     */
    p_component<T> get_Component(const int& ID) const
    {
        for (const auto& component : _components)
            if (component->get_ID() == ID)
                return component;
        
        return nullptr;
    }
};