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

void cable_allocator::generate_region_table()
{
    // Log the cavity combination.
    auto generate_region_key = [&](std::vector<int> path)
    {
        std::sort(path.begin(), path.end());
        std::string key;
        for(const auto& ID : path)
            key += std::to_string(ID);
        return key;
    };

    // For every cables
    for(const auto& cable : _cables)
    {
        for(const auto& [gauge, wires] : cable._container)
        {
            std::unordered_set<std::string> logged_region;
            std::vector<cable_region> current_cable_regions;

            // Search only in compatibles cavities
            for(const auto& compatible_cavity : _connector.get_compatible_cavitiy_list(gauge))
            {
                std::vector<int> path;
                std::unordered_set<int> visited;
                
                // DFS core
                std::function<void(cavity)> dfs = [&](cavity current) 
                {
                    // Return to previous if current cavity is not available
                    if(!current.is_available()) return;
                    else
                    {
                        // Log current node
                        auto current_cavity_ID = current.get_ID();
                        visited.insert(current_cavity_ID);
                        path.push_back(current_cavity_ID);

                        // Stop condition : A region is found
                        if (path.size() == cable.size(gauge)) 
                        {
                            // Check if it is not a duplicate 
                            auto key = generate_region_key(path);
                            if (!logged_region.count(key)) 
                            {
                               // Save the region found
                               logged_region.insert(key);
                               auto valid_region = cable_region(cable.get_ID(), path, gauge);
                               current_cable_regions.push_back(valid_region);
                            }
                        }
                        else // Continue to build the region with adjacent node.
                            for (const auto& neighbor : _connector.get_adjacency_list(current_cavity_ID)) 
                                if (neighbor.is_available() && !visited.count(neighbor.get_ID())) 
                                    dfs(neighbor);
                    
                        // Return to previous node
                        visited.erase(current_cavity_ID);
                        path.pop_back();
                        return;
                    }
                };

                dfs(*compatible_cavity);
            }
            _region_table.push_back(current_cable_regions);
        }
    }
}

void cable_allocator::allocate_cables() 
{
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

    dfs(0); 
}

void cable_allocator::print_region_list()
{
    std::ofstream log_file("cable_possible_region.txt");
    for(auto [cable, region_table] : std::views::zip(_cables,_region_table))
    {
        std::print(log_file,"possible choice for cable {}:\n",cable.get_ID());

        for(auto& item : region_table)
        {
            for(auto& cavity : item.get_list())
                std::print(log_file,"{} ",cavity);
            std::print(log_file,"\n");
        }
    }
    log_file.close();
}

void cable_allocator::print_solutions()
{
    std::ofstream log_file("cable_allocation_solution.txt");
    for(auto const [i, solution] : std::views::enumerate(_solutions))
    {
        std::print(log_file, "Possible solution : {}\n", i+1 );
        for(auto const [j, regions] : std::views::enumerate(solution))
        {
            auto list = regions.get_list();
            std::print(log_file,"cable {}:\n", j+1 );
            for(auto& element : list)
                std::print(log_file,"{} ",element);
            std::print(log_file,"\n");
        }
        std::print(log_file,"\n");
    }
    log_file.close();
}