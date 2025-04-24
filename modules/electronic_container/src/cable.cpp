/**
 * @file cable.cpp
 * @author
 * HUANG He (he.huang.intern@3ds.com)
 * @brief
 * Implementation of the cable class.
 * @version 1.3
 * @date 2025-04-22
 * @copyright
 * Dassault Systemes 2025
 *
 */
#include "cable.h"

#include <set>
#include <algorithm>
#include <ranges>

bool cable::generate_allocations(int mode)
{
    std::vector<sp_component<cavity>> range;
    
    if (_container.empty()) return false; // No wires to allocate
    else if (auto sp_connector = _wp_connector.lock())
    {
        if(mode == 1)
        {
            auto result = 
            std::views::all(sp_connector->_container) |
            std::views::filter([&](const auto& obj) { return obj->status() != 0; }) |
            std::views::transform([&](const auto& obj) { 
                return sp_connector->get_adjacency_list(obj->get_ID()); 
            }) |
            std::views::join |
            std::ranges::to<std::vector<int>>(); 
        
        std::set<int> unique_ids(result.begin(), result.end());
        
        range = 
            unique_ids |
            std::views::transform([&](int id) { return sp_connector->get_component(id); }) |
            std::ranges::to<std::vector<sp_component<cavity>>>();
        }
        else range = sp_connector->_container;
            
        
    
        for (const auto& path_head_cavity : range)
        {
            std::set<int> visited_cavity_indices;
            
            auto dfs =  
            [&](auto&& self,                 
                int cavity_ID,
                int wire_index) -> void
            {
                auto current_cavity = sp_connector->get_component(cavity_ID);
                if (current_cavity->status()) return; // Cavity is already occupied
                auto current_wire     = _container[wire_index];
                if (!current_cavity->is_compatible(*current_wire)) return; // cavity not compatible
                
                // Log the searching path
                visited_cavity_indices.insert(cavity_ID);
                
                if (visited_cavity_indices.size() == _container.size()) // Save valid complete regions
                    _allocations.emplace(visited_cavity_indices, sp_connector);
                
                else // Continue searching through available neighbors
                    for (const auto& neighbor : sp_connector->get_adjacency_list(cavity_ID))
                        if (!visited_cavity_indices.count(neighbor))
                            self(self, neighbor, wire_index + 1);
    
                // Backtrack
                visited_cavity_indices.erase(cavity_ID);
            };
            dfs(dfs, path_head_cavity->get_ID(), 0); 
        }
        return !_allocations.empty();
    }
    else return false; // Connector is not valid
}

void cable::add_wires(const std::vector<std::tuple<int, int>> &wires)
{
    auto wire_index = 0;
    for (const auto& [wire_gauge, num_wires] : wires)
        for (auto i = 0; i < num_wires; ++i)
            _container.emplace_back(std::make_shared<wire>(wire_index++, wire_gauge));
}

void cable::confirme_allocation(int current_cable_ID, int allocation_ID)
{
    auto iter = std::next(_allocations.begin(),allocation_ID);
    auto layout = (*iter).get_layout();
    if(auto promoted_connector_ptr = _wp_connector.lock())
        for(const auto& allocated_cavity_ID : layout)
            promoted_connector_ptr->get_component(allocated_cavity_ID)->allocate_to_cable(current_cable_ID);
}
