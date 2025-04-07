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

cable_allocator::cable_allocator(const std::vector<cavity>& cavities, 
                                 const std::vector<cable>&  cables) :
    _connector(cavities),
    _cables(cables)
    {
        generate_region_table();
        allocate_cables();
    }
bool cable_allocator::add_cable(cable new_cable)
{
 
    _region_pool[new_cable];
    bool cable_added = false;

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
                        _region_pool.at(new_cable).emplace(new_cable.get_ID(), gauge, path);
                    
                    else // Continue to build the region with adjacent node.
                        for (const auto& neighbor : _connector.get_adjacency_list(current_cavity_ID)) 
                            if (neighbor.is_available() && !visited.count(neighbor.get_ID())) 
                                if(self(self, neighbor, wire_index + 1)) return true;
                    
                    // Return to previous node
                    visited.erase(current_cavity_ID);
                    path.pop_back();
                    wire_index--;

                    return false;
                }
            };
            cable_added = dfs(dfs, *compatible_cavity, 0);
        }
    }
    return cable_added;
}

void cable_allocator::generate_region_table()
{
   for(auto& cable : _cables)
   {
        add_cable(cable);
   }
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

void cable_allocator::print_region_list()
{
    std::ofstream log_file("cable_possible_region.txt");
    for(auto [cable, cavity_map] : _region_pool)
    {
        std::print(log_file,"possible choice for cable {}:\n",cable.get_ID());

        for(auto& region : cavity_map)
        {
            auto layout = region.get_layout(); 
            for(auto& [wire, cavity] : layout)
                std::print(log_file,"wire {} : cavity {}\n", wire, cavity);

            std::print(log_file,"\n");
        }
    }
    log_file.close();
}

void cable_allocator::print_solutions()
{
    /*std::ofstream log_file("cable_allocation_solution.txt");
    for(auto const [i, solution] : std::views::enumerate(_solutions))
    {
        std::print(log_file, "Possible solution : {}\n", i+1 );
        for(auto const [j, regions] : std::views::enumerate(solution))
        {
            auto list = regions.get_layout();
            std::print(log_file,"cable {}:\n", j+1 );
            for(auto& [wire, cavity] : list)
                std::print(log_file,"wire } : cable : {} ", wire, cavity);
            std::print(log_file,"\n");
        }
        std::print(log_file,"\n");
    }
    log_file.close();*/
}