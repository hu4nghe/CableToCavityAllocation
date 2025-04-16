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

#include <cmath>
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
        std::views::transform([](const auto& tup)
        { 
            return std::make_from_tuple<cavity>(tup); 
        }) | 
        std::ranges::to<std::vector>()){}


// Helper function to update the circle when a new cavity is added
void update_circle(std::pair<double, double>& center, double& radius, const cavity& cav)
{
    double dist = cav.distance(center);
    
}

std::vector<std::tuple<int,int>> cable_allocator::add_cable(int cable_ID, const std::vector<std::tuple<int, int>>& wires)
{
    auto new_cable = cable(
        cable_ID,
        wires | 
        std::views::transform([](const auto& tup)
        { 
            return std::make_from_tuple<wire>(tup); 
        }) | 
        std::ranges::to<std::vector>());

    _region_pool[new_cable];

    for(const auto& cavity_head : _connector._container)
    {
        std::vector<std::pair<int, int>> path;
        std::unordered_set<int> visited;
        std::pair<double, double> center;
        double radius{};
        
        auto dfs =  
        [&](auto&& self,                 
            int cavity_ID,                 
            int wire_index) -> void
        {
            if(!_connector.is_available(cavity_ID) ||
               !wire_index >= new_cable.size()) return;

            auto current_wire   = new_cable._container[wire_index];
            auto current_cavity = _connector.get_Component(cavity_ID);
            
            // Check if the cavity is compatible with the wire
            if (!current_cavity->is_compatible(*current_wire)) return;
            // Log the searching path
            visited.insert(cavity_ID);
            path.emplace_back(current_wire->get_ID(), cavity_ID);

            auto old_raius = radius;
            auto old_center = center;

            double max_dist{};
            std::pair<p_component<cavity>, 
                      p_component<cavity>> furtherst_cavity;
            for(const auto& [_, i] : path)
            {
                auto selected_cavity_i = _connector.get_Component(i);
                for(const auto& [_, j] : path)
                {
                    auto selected_cavity_j =_connector.get_Component(j);
                    double current_dist{};
                    if( i == j ) 
                        current_dist = 0;
                    else
                        current_dist = selected_cavity_i->distance(*selected_cavity_j);

                    if( current_dist >= max_dist)
                    {
                        max_dist = current_dist;
                        furtherst_cavity = std::make_pair(selected_cavity_i, selected_cavity_j);
                    }
                }
            }
            if(furtherst_cavity.first == furtherst_cavity.second) radius = 0;
            radius = furtherst_cavity.first->distance(*furtherst_cavity.second) / 2.0;
            center = furtherst_cavity.first->generate_center(*furtherst_cavity.second);
            
            // Save valid complete regions
            if (path.size() == new_cable.size())
                _region_pool.at(new_cable).emplace_back(path, radius);
            else // Continue searching through available neighbors
                for (const auto& neighbor : _connector.get_adjacency_list(cavity_ID))
                    if (!visited.count(neighbor))
                        self(self, neighbor, wire_index + 1);
        
            // Backtrack
            visited.erase(cavity_ID);
            path.pop_back();
            radius = old_raius;
            center = old_center;    
        };
        dfs(dfs, cavity_head->get_ID(), 0); 
    }
    
    // Result sender
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
