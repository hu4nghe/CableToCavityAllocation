/**
 * @file electronic_component_base.h
 * @author
 * HUANG He (he.huang.intern@3ds.com)
 * @brief
 * Electronic components(wire and cavity) base class
 * @version 3.0
 * @date 2026-04-01
 *
 * @copyright
 * Dassault Systemes 2025
 *
 */
#pragma once

#include <utility>

#include "AWG.h"

class electronic_component_base
{
    protected:

    const int _ID;
    const AWG _gauge;

    public:

    /**
     * @brief
     * Deleted default constructor
     * Please allocate an ID for every electronic component.
     *
     */
    electronic_component_base() = delete;

    /**
     * @brief
     * Default destructor.
     *
     */
    virtual ~electronic_component_base() = default;

    /**
     * @brief
     * Base class constructor.
     *
     * @param id Component's ID.
     * @param gauge Component's size in American Wire Gauge.
     */
    electronic_component_base(
        int ID,
        int gauge)
        : _ID(ID),
          _gauge(static_cast<AWG>(gauge))
    {}

    /**
     * All component is unique, identified with ID.
     * You do not want to copy a component.
     */
    electronic_component_base(const electronic_component_base&) =
        delete;
    electronic_component_base& operator=(
        const electronic_component_base&) = delete;
    electronic_component_base& operator=(
        electronic_component_base&&) = delete;

    /**
     * @brief
     * Base move constructor.
     *
     * @param other Another electronic_component_base object to
     * move.
     */
    explicit electronic_component_base(
        electronic_component_base&& other)
        : _ID(other._ID),
          _gauge(std::move(other._gauge))
    {}

    /**
     * @brief
     * Overrided operator< for std::set/std::map
     *
     * @param other Another electronic component
     * @return true If current object's ID is inferior than the
     * other's.
     * @return false If current object's ID is superior than the
     * other's.
     */
    bool operator<(const electronic_component_base& other) const
    {
        return _ID < other._ID;
    }

    /**
     * @brief
     * Overrided operator==.
     *
     * @param other Another electronic component
     * @return true If current object's ID is the same to the
     * other's.
     * @return false If current object's ID is different from the
     * other's.
     */
    bool operator==(const electronic_component_base& other) const
    {
        return _ID == other._ID;
    }

    /**
     * @brief
     * Check if two component can fit each other.
     *
     * @param other Another electronic_component_base object.
     * @return true If two components have the same gauge.
     * @return false If two components have differents gauges.
     */
    bool is_compatible(const electronic_component_base& other) const
    {
        return _gauge == other._gauge;
    }

    /**
     * @brief
     * Get current cavity's gauge.
     *
     * @return const AWG Cavity's AWG.
     */
    const AWG get_gauge() const
    {
        return _gauge;
    }

    /**
     * @brief
     * Get current cavity's ID.
     *
     * @return const int Cavity's ID.
     */
    const int get_ID() const
    {
        return _ID;
    }
};

#include <functional>
namespace std
{
    /**
     * @brief
     * Hash function for electronic_component_base for STL unordered
     * container
     *
     */
    template <> struct hash<electronic_component_base>
    {
        size_t operator()(
            const electronic_component_base& comp) const
        {
            return std::hash<int>()(comp.get_ID());
        }
    };
} // namespace std