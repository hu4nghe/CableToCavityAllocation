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
#include <print>
#include <ranges>

cable_allocator::cable_allocator(const std::vector<cavity>& cavities, 
                                 const std::vector<cable>& cables) :
    _connector(cavities),
    _cables(cables){}

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
    // Generate segment of region for cross check
    auto generate_region_segments = [&](std::vector<int> path)
    {
        std::set<std::pair<int, int>> segments;
            for (const auto& i : path) 
                for (const auto& j : path) 
                    if(i == j) continue;
                    else segments.insert(i < j ? std::make_pair(i, j) : std::make_pair(j, i));
        
        return segments;
    };

    for(const auto& cable : _cables)
    {
        for(const auto& wire_gauge_pair : cable._container)
        {
            const auto current_gauge = wire_gauge_pair.first;
            const auto wires_in_current_gauge = wire_gauge_pair.second;
            // Search only in compatibles cavities
            auto compatible_cavities = _connector.get_compatible_cavitiy_list(current_gauge);

            std::unordered_set<std::string> logged_region;
            std::vector<cable_region> current_cable_regions;

            for(const auto& start : compatible_cavities)
            {
                std::vector<int> path;
                std::unordered_set<int> visited;
            
                std::function<void(cavity)> dfs = [&](cavity current) 
                {
                    visited.insert(current.get_ID());
                    path.push_back(current.get_ID());
                    if (path.size() == cable.size(current_gauge)) 
                    {
                        auto key = generate_region_key(path);
                        if (!logged_region.count(key)) 
                        {
                            logged_region.insert(key);
                            auto segments = generate_region_segments(path);
                            auto valid_region = cable_region(path, segments);
                            current_cable_regions.push_back(valid_region);
                        }
                    
                        visited.erase(current.get_ID());
                        path.pop_back();
                        return;
                    }
                
                    // Search path in current cavity's adjacency_list
                    auto adj_list = _connector.get_adjacency_list(current.get_ID());

                    for (const auto& neighbor : adj_list) 
                        if (neighbor.is_available() && !visited.count(neighbor.get_ID())) 
                            dfs(neighbor);

                    visited.erase(current.get_ID());
                    path.pop_back();
                };
                dfs(*start);
            }
            _region_table.push_back(current_cable_regions);

        }
        
    }
}

void cable_allocator::print_region_list()
{
    for(auto [cable, region_table] : std::views::zip(_cables,_region_table))
    {
        std::print("possible choice for cable {}:\n",cable.get_ID());

        for(auto& item : region_table)
        {
            for(auto& cavity : item.get_list())
                std::print("{} ",cavity);
            std::print("\n");
        }
    }
}