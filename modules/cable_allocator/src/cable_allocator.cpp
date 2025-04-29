/**
 * @file cable_allocator.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocator class.          
 * @version 1.4
 * @date 2025-04-25
 * 
 * @copyright 
 * Dassault Systemes 2025

 */

#include "cable_allocator.h"

bool cable_allocator::add_cable(const std::vector<std::tuple<int, int>>& wires, int mode)
{
    auto new_cable = cable(_sp_connector);
    new_cable.add_wires(wires);
    if (new_cable.generate_allocations(mode))
        _cable_list.push_back(new_cable);
    else
        return false;
    return true;
}

void cable_allocator::confirme_allocation(int cable_ID, int allocation_idx)
{
    if (cable_ID < 1 || cable_ID > _cable_list.size()) 
        throw std::out_of_range("Cable index out of range.");
    else _cable_list.at(cable_ID - 1 ).confirme_allocation(cable_ID, allocation_idx); 
}