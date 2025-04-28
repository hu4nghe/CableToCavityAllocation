/**
 * @file cable.cpp
 * @author
 * HUANG He (he.huang.intern@3ds.com)
 * @brief
 * Implementation of the cable class.
 * @version 1.4
 * @date 2025-04-25
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#include "cable.h"

#include <ranges>

bool cable::generate_allocations(int mode)
{
    connector seraching_range;
    
    if (_container.empty()) return false; // No wires to allocate
    else if (auto sp_connector = _wp_connector.lock())
    {
        if (mode == 1)
        {
            // Search only the places near the allocated cavities.
            seraching_range = *sp_connector
                // Find allocated cavities.
                | std::views::filter([&](const auto& obj){return obj->status() != 0;})
                // Get their adjacent cavities.
                | std::views::transform([&](const auto& obj){return sp_connector->get_adj_list(obj->get_ID());})
                // Flatten the adjacent cavities's index.
                | std::views::join
                // Turn result into a cavity index vector.
                | std::ranges::to<std::vector<int>>()
                // Retrive the cavity object by ID.
                | std::views::transform([&](int id){return sp_connector->get_component(id);})
                // Build the searching seraching_range vector.
                | std::ranges::to<connector>();
        }
        else seraching_range = *sp_connector;
            
        for (const auto& path_head_cavity : seraching_range)
        {
            std::set<int> visited_cavity_indices;
            
            auto dfs =  
            [&](auto&& self,                 
                int    cavity_ID,
                int    wire_index)
            {
                auto current_cavity = sp_connector->get_component(cavity_ID);
                if (current_cavity->status()) return; // Cavity is already occupied
                auto current_wire   = _container[wire_index];
                if (!current_cavity->is_compatible(*current_wire)) return; // cavity not compatible
                
                // Log the searching path
                visited_cavity_indices.insert(cavity_ID);
                
                if (visited_cavity_indices.size() == size()) // Save valid complete regions
                    _allocations.emplace(visited_cavity_indices, sp_connector);
                
                else // Continue searching through available neighbors
                    for (const auto& neighbor : sp_connector->get_adj_list(cavity_ID))
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
    if (auto promoted_connector_ptr = _wp_connector.lock())
        for (const auto& allocated_cavity_ID : layout)
            promoted_connector_ptr->get_component(allocated_cavity_ID)->allocate_to_cable(current_cable_ID);
    
    _allocations.clear();
    _is_allocated = true;
}
