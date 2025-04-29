/**
 * @file cable.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a cable, who includes multiples wires
 * @version 1.4
 * @date 2025-04-25
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#pragma once

#include "electronic_container_base.h"
#include "connector.h"
#include "cable_allocation.h"

class cable : public electronic_container_base<wire>
{
private : 

    std::set<cable_allocation>    _allocations;
    std::weak_ptr<connector>      _wp_connector;
    bool                          _is_allocated;

public :

    /**
     * @brief 
     * Construct a new cable object
     * 
     * @param _sp_connector The connector's shared_ptr where we allocate the cable.
     */
    cable(std::shared_ptr<connector> _sp_connector) : 
        _wp_connector(_sp_connector),
        _is_allocated(false) {}
    
    /**
     * @brief 
     * Add wires to cable. 
     * 
     * @param wires A vector, each element indicates the wire's gauge and number.
     */
    void add_wires(const std::vector<std::tuple<int, int>>& wires);

    /**
     * @brief 
     * Generate possible allocations for current cable on the conncetor.
     * 
     * @param searching_range 1 to search allocations adjacent to placed cables. 
     *                        Others to select all allocations.
     * @return true If at least one allocation is found.
     * @return false If there is no allocation found.AIO_PRIO_DELTA_MAX
     * 
     * @throw std::runtime_error If connector pointer is expired.
     */
    bool generate_allocations(int mode);

    /**
     * @brief 
     * Applicate a allocation on current cable.
     * This will clear _allocations, you need to regenerated it after to keep it up to date.
     * 
     * @param current_cable_ID Current Cable ID (which is externally managed by cable_allocator.)
     * @param allocation_ID ID of the allocation that we want to applicate.
     * 
     * @throw std::out_of_range If allocation ID is not valid.
     */
    void confirme_allocation(int current_cable_ID, int allocation_ID);

    /**
     * @brief 
     * Return a set that includes all allocations.
     * 
     * @return std::set<cable_allocation> Allocations for current cable.
     */
    const auto& get_allocations() const { return _allocations; }

    /**
     * @brief 
     * Get cable status.
     * 
     * @return true If cable is allocated.
     * @return false If cable is not allocated.
     */
    bool is_allocated() const { return _is_allocated; }

};