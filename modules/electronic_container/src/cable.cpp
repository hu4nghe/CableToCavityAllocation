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

bool cable::generate_allocations()
{
    if (_container.empty()) return false; // No wires to allocate
    else if (auto sp_connector = _wp_connector.lock())
    {
        for (const auto& cavity_head : sp_connector->_container)
        {
            std::vector<std::pair<int, int>> dfs_path;
            std::set<int> visited_cavity_indices;
            
            auto dfs =  
            [&](auto&& self,                 
                int cavity_ID,                 
                int wire_index) -> void
            {
                if (wire_index >= _container.size()) return; //wire index is out of range
                auto current_wire     = _container[wire_index];
                auto current_cavity = sp_connector->get_component(cavity_ID);
                if (current_cavity->status()) return; // Cavity is already occupied
                if (!current_cavity->is_compatible(*current_wire)) return; // cavity not compatible
    
                // Log the searching path
                visited_cavity_indices.insert(cavity_ID);
                dfs_path.emplace_back(current_wire->get_ID(), cavity_ID);
                
                if (dfs_path.size() == _container.size()) // Save valid complete regions
                    _allocations.emplace_back(visited_cavity_indices, sp_connector);
                else // Continue searching through available neighbors
                    for (const auto& neighbor : sp_connector->get_adjacency_list(cavity_ID))
                        if (!visited_cavity_indices.count(neighbor))
                            self(self, neighbor, wire_index + 1);
    
                // Backtrack
                visited_cavity_indices.erase(cavity_ID);
                dfs_path.pop_back();
            };
            dfs(dfs, cavity_head->get_ID(), 0); 
        }
        std::ranges::sort(_allocations, {}, &cable_allocation::get_score);
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
    auto layout = _allocations.at(allocation_ID).get_layout();
    if(auto promoted_connector_ptr = _wp_connector.lock())
        for(const auto& allocated_cavity_ID : layout)
            promoted_connector_ptr->get_component(allocated_cavity_ID)->allocate_to_cable(current_cable_ID);
}
