/**
 * @file electronic_container_base.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Electronic containers base class
 * @version 1.3
 * @date 2025-04-22
 * 
 * @copyright 
 * Dassault Systemes 2025
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

    std::vector<sp_component<T>> _container;

public:
    friend class cable_allocator;
  
    electronic_container_base() = default;

    /**
     * @brief 
     * Construct a new electronic container base object
     * Automatically determines the type of component based on the the parameter type.
     * std::tuple<int, int> for wire objects
     * std::tuple<int, int, double, double> for cavity objects
     * @param components A vector containing all components's data. 
     */
    template <typename tuple_type>
    electronic_container_base(const std::vector<tuple_type>& components)
    {
        // type checking
        if constexpr (std::is_same_v<T, wire>)
            static_assert(std::is_same_v<tuple_type, std::tuple<int, int>>,
                          "Expecte tuple<int, int> for wire objects");
        if constexpr (std::is_same_v<T, cavity>)
            static_assert(std::is_same_v<tuple_type, std::tuple<int, int, double, double>>,
                          "Expecte tuple<int, int, double, double> for cavity objects");
                          
        for (const auto& p : components)
            _container.push_back(std::make_shared<T>(std::make_from_tuple<T>(p)));
    }

    /**
     * @brief 
     * Get a component by its ID.
     * 
     * @param ID The ID of the component to retrieve.
     * @return A shared pointer to the component, or nullptr if not found.
     */
    sp_component<T> get_component(const int& ID) const
    {
        for (const auto& component : _container)
            if (component->get_ID() == ID)
                return component;
        
        return nullptr;
    }
};