/**
 * @file cable_allocator.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocator class.          
 * @version 2.0
 * @date 2025-07-09
 * 
 * @copyright 
 * Dassault Systemes 2025

 */
#include "cable_allocator.h"

#include <ranges>
#include <stdexcept>

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

auto cable_allocator::get_cable_allocations(int cable_ID) -> std::set<std::tuple<AllocationScore, std::set<int>>> const 
{
    if (cable_ID < 1 || cable_ID > _cable_list.size()) 
        throw std::out_of_range("Cable index out of range.");
    else return _cable_list.at(cable_ID - 1).get_allocations()
        | std::views::transform([](const auto& a)
                                {
                                    return std::tuple(a.get_score(), 
                                                      a.get_layout());
                                }) 
        | std::ranges::to<std::set>();
}

void cable_allocator::confirme_allocation(int cable_ID, int allocation_idx)
{
    if (cable_ID < 1 || cable_ID > _cable_list.size()) 
        throw std::out_of_range("Cable index out of range.");
    else _cable_list.at(cable_ID - 1 ).confirme_allocation(cable_ID, allocation_idx); 
}

auto cable_allocator::get_connector_status() -> std::vector<int> const
{
    return *(_sp_connector)
        | std::views::transform([](const auto& c)
                                {
                                    return c->status();
                                })  
        | std::ranges::to<std::vector>();
}