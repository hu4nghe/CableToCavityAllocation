/**
 * @file cable_allocator.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocator class.          
 * @version 1.3
 * @date 2025-04-22
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "cable_allocator.h"

#include <ranges>
cable_allocator::cable_allocator(const std::vector<std::tuple<int, int, double, double>>& cavity_data) :
    _sp_connector(std::make_shared<connector>(cavity_data)){}

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

auto cable_allocator::get_cable_allocations(int cable_ID) const -> std::set<std::tuple<double, std::set<int>>>
{
    std::set<std::tuple<double, std::set<int>>> result;

    auto cable = _cable_list.at(cable_ID - 1);
    for(const auto& cable_allocation : cable.get_allocations())
        result.emplace(cable_allocation.get_score(), cable_allocation.get_layout());
        
    return result;
}

void cable_allocator::confirme_allocation(int cable_ID, int allocation_idx)
{ 
    _cable_list.at(cable_ID - 1 ).confirme_allocation(cable_ID, allocation_idx); 
}
