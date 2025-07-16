/**
 * @file electronic_container_base.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The electronic containers base class
 * @version 2.0
 * @date 2025-07-09
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#pragma once

#include "cavity.h"
#include "wire.h"

#include <memory>
#include <concepts>

/**
 * @brief 
 * Define a wire and cavity type concept for difference init data.
 * std::tuple<int, int> for wire objects.
 * std::tuple<int, int, double, double> for cavity objects.
 *  
 */
template <typename T>
concept is_wire_component = std::is_same_v<T, wire>;

template <typename T>
concept is_cavity_component = std::is_same_v<T, cavity>;

template <typename T, typename tuple_type>
concept electronic_component_data_type =
    (is_wire_component  <T> && std::is_same_v<tuple_type, std::tuple<int, int>>) ||
    (is_cavity_component<T> && std::is_same_v<tuple_type, std::tuple<int, int, double, double>>);

template <typename T>
class electronic_container_base
{
    using container_t = std::vector<std::shared_ptr<T>>;
    
protected :
    
    container_t _container;

public :
    
    /**
     * @brief 
     * Default constructor for electronic container base object
     * 
     */
    electronic_container_base() = default;

    /**
     * @brief 
     * Construct a new electronic container base object.
     * Automatically determines the type of component based on the the parameter type.
     *
     * @param components A vector containing all components's data.
     */
    template <typename tuple_type>
        requires electronic_component_data_type<T, tuple_type>
    electronic_container_base(const std::vector<tuple_type>& components)
    {
        for (const auto& p : components)
            _container.push_back(std::make_shared<T>(std::make_from_tuple<T>(p)));
    }

    /**
     * @brief 
     * Get a component by its ID.
     * 
     * @param ID The ID of the component to retrieve.
     * @return A shared_ptr to the component.
     */
    std::shared_ptr<T> get_component(const int& ID) const
    {
        auto iter = std::ranges::find(_container, ID, &electronic_component_base::get_ID);
        return iter == _container.end() ? nullptr : *iter;
    }

    /**
     * @brief 
     * Add iterator support(begin()) for range based for.
     * 
     * @return auto _container.begin()
     */
    auto begin() const { return _container.begin(); }

    /**
     * @brief 
     * Add iterator support(end()) for range based for.
     * 
     * @return auto _container.end()
     */
    auto end() const { return _container.end(); }

    /**
     * @brief 
     * Operator[] to imitate vector's behavior.(No boudary check.)
     * 
     * @param index key
     * @return auto value
     */
    auto operator[](std::size_t index) const{ return _container[index]; }

    /**
     * @brief 
     * at() to imitate vector's behavior.(With boundary check.)
     * 
     * @param index key
     * @return auto value
     */
    auto at(std::size_t index) const{ return _container.at(index); }

    /**
     * @brief 
     * size() to imitate vector's behavior.
     * 
     * @return std::size_t _container's size. 
     */
    auto size() const { return _container.size(); }

    /**
     * @brief 
     * insert() to imitate vector's behavior (Adapt to std::ranges)
     * 
     * @param pos A const iterator of vector
     * @param ptr Object pointer to insert
     * @return auto _containter.insert() return value.
     */
    auto insert(container_t::const_iterator pos, 
                std::shared_ptr<T>          ptr) { return _container.insert(pos, ptr); }

};