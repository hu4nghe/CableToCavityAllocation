/**
 * @file cable_allocator.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocator class.          
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "cable_allocator.h"

#include <unordered_set>
#include <iostream>
#include <print>
#include <sstream>
#include <ranges>
#include <fstream>
#include <functional>


cable_allocator::cable_allocator(const std::vector<std::tuple<int, int, double, double>>& cavities) :
    _connector(
        cavities | 
        std::views::transform([](const auto& tup){ return std::make_from_tuple<cavity>(tup); }) | 
        std::ranges::to<std::vector>())
        {
            for(auto& element : _connector._container)
            {
                std::print("Cavity ID: {}\n", element->get_ID());   
                std::print("Cavity Size: {}\n\n", static_cast<int>(element->get_gauge()));
            }
        }

std::vector<std::tuple<int,int>> cable_allocator::add_cable(int cable_ID, const std::vector<std::tuple<int, int>>& wires)
{
    auto new_cable = cable(
        cable_ID,
        wires | 
        std::views::transform([](const auto& tup){ return std::make_from_tuple<wire>(tup); }) | 
        std::ranges::to<std::vector>());

    _region_pool[new_cable];

    for(const auto& cavity : _connector._container)
    {
        std::vector<std::pair<int, int>> path;
        std::unordered_set<int> visited;
        auto dfs =  
        [&](auto&& self,                 
            int cavity_ID,                 
            int wire_index) -> void
        {
            if(!_connector.is_available(cavity_ID) ||
               !wire_index >= new_cable.size()) return;

            auto wire   = new_cable._container[wire_index];
            auto cavity = _connector.get_Component(cavity_ID);
            
            // Check if the cavity is compatible with the wire
            if (!cavity->is_compatible(*wire)) return;
            // Log the searching path
            visited.insert(cavity_ID);
            path.emplace_back(wire->get_ID(), cavity_ID);

            // Save valid complete regions
            if (path.size() == new_cable.size())
                _region_pool.at(new_cable).emplace_back(path);
            else // Continue searching through available neighbors
                for (const auto& neighbor : _connector.get_adjacency_list(cavity_ID))
                    if (!visited.count(neighbor))
                        self(self, neighbor, wire_index + 1);
        
            // Backtrack
            visited.erase(cavity_ID);
            path.pop_back();
        };
        dfs(dfs, cavity->get_ID(), 0); 
    }
    std::vector<std::tuple<int,int>> result;

    for(const auto& allocations : _region_pool.at(new_cable))
    {
        auto allocation_map = allocations.get_layout();
        for(const auto& [wire, cavity] : allocation_map)
            result.emplace_back(wire, cavity);
    }

    return result;
}

void cable_allocator::connect(std::map<int, int> connections)
{
    for(const auto& [wire_idx, cavity_idx] : connections)
        for(auto& [cable, _] : _region_pool)
            _connector.get_Component(cavity_idx)->connect(cable.get_Component(wire_idx));
}
