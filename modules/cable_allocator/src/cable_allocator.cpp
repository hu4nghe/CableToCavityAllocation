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
#include "cavity.h"

cable_allocator::cable_allocator(const std::vector<std::tuple<int, int, double, double>>& cavity_data) :
    _sp_connector(std::make_shared<connector>(cavity_data)){}

bool cable_allocator::add_cable(const std::vector<std::tuple<int, int>>& wires)
{
    auto new_cable = cable(_sp_connector);
    new_cable.add_wires(wires);
    _cable_list.push_back(new_cable);
    if (new_cable.generate_allocations())
        return true;
    else
        _cable_list.pop_back();
    
    return false;
}

auto cable_allocator::get_allocations(int cable_ID) const -> std::vector<cable_allocation>
{
    auto cable = _cable_list.at(cable_ID);

    if (cable.generate_allocations())
        return cable.get_allocations();
    else
        return std::vector<cable_allocation>{};
}
