/**
 * @file cable_allocator.cpp
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * @version 1.0
 * @date 2025-04-02
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#include "cable_allocator.h"

#include <unordered_set>
#include <functional>

// Headers for debug use output only, to remove before release.
#include <print>
#include <ranges>
#include <fstream>
#include <filesystem>
#include <iostream>

cable_allocator::cable_allocator(const std::vector<cavity>& cavities) :
    _connector(cavities){}

void cable_allocator::add_cable(cable new_cable)
{
    _region_pool[new_cable];

    for(const auto& [gauge, wires] : new_cable._container)
    {
        // Search only in compatibles cavities
        for(const auto& compatible_cavity : _connector.get_compatible_cavitiy_list(gauge))
        {
            std::vector<std::pair<int,int>> path;
            std::unordered_set<int>         visited;
                
            auto dfs = 
            [&](auto&& self, 
                const cavity& current, 
                int wire_index) -> bool
            {
                // Return to previous if current cavity is not available
                if(!current.is_available()) return false;
                else
                {
                    // Log the searching path in wire - cavity mapping.
                    auto current_cavity_ID = current.get_ID();
                    auto current_wire_ID   = wires[wire_index]->get_ID();
                    visited.insert(current_cavity_ID);
                    path.emplace_back(current_wire_ID,
                                      current_cavity_ID);

                    // When a valid region is found, save it to region pool.
                    if (path.size() == new_cable.size(gauge)) 
                        _region_pool.at(new_cable).emplace_back(new_cable.get_ID(), gauge, path);
                    
                    else // Continue to build the region with adjacent node.
                        for (const auto& neighbor : _connector.get_adjacency_list(current_cavity_ID)) 
                            if (_connector.get_Component(neighbor)->is_available() && !visited.count(neighbor)) 
                                if(self(self, *(_connector.get_Component(neighbor)), wire_index + 1)) return true;
                    
                    // Return to previous node
                    visited.erase(current_cavity_ID);
                    path.pop_back();
                    wire_index--;

                    return false;
                }
            };
            dfs(dfs, *compatible_cavity, 0);
        }
    }

    //print results : 
    const auto& regions = _region_pool.at(new_cable);

    std::print("possible choice for current cable ({}):\n",new_cable.get_ID());
    for(const auto& [i, region] : std::views::enumerate(regions))
    {
        std::print("Allocation {} :\n", i + 1);

        for (const auto& [wire, cavity] : region.get_layout())
            std::print("wire {} : cavity {}\n", wire, cavity);
        
        std::print("\n");
    }
        
    std::print("Chose a allocation to continue.\n");
    int choice = 0;
    std::cin>>choice;
    std::print("Allocation {} is validated.\n\n", choice);

    auto connected_idx = _region_pool.at(new_cable)[choice -1].get_layout();
    connect(connected_idx);
}

void cable_allocator::allocate_cables() 
{
    /*
    std::vector<cable_region> current_solution;

    std::function<void(int)> dfs = [&](int cable_index) 
    {
        if (cable_index == _cables.size()) 
        {
            _solutions.push_back(current_solution); // Store valid assignment
            return;
        }

        const auto& regions = _region_table[cable_index];

        for (const auto& region : regions) 
        {
            auto region_cavities = region.get_list(); 
            auto gauge = region.get_gauge();

            // Check if the region contains any unavailable cavities
            if (region.has_unavailable_cavity(_connector.get_unavailable_index_pool(gauge)))
                continue;

            // Assign cable to this region
            current_solution.push_back(region);
            _connector.set_availability(region_cavities, false);

            // Recur to assign the next cable
            dfs(cable_index + 1);

            // Backtrack
            current_solution.pop_back();
            _connector.set_availability(region_cavities, true);
        }
    };

    dfs(0); */
}

void cable_allocator::connect(std::map<int, int> connections)
{
    for(const auto& [wire_idx, cavity_idx] : connections)
        for(auto& [cable, _] : _region_pool)
            _connector.get_Component(cavity_idx)->connect(cable.get_Component(wire_idx));
}

void cable_allocator::print_current_solutions()
{
    _connector.print_current_connector_status();
}