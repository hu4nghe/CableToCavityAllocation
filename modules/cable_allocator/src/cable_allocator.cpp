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

cable_allocator::cable_allocator(const std::vector<cavity>& cavities, const std::vector<cable>& cables) :
    _connector(cavities),
    _cables(cables){}

void cable_allocator::generate_region_table()
{
    for(const auto& cable : _cables)
    {
        auto compatible_cavities = _connector.get_compatible_cavitiy_list(cable.get_gauge());

        std::unordered_set<std::string> seen;
        std::vector<cable_region> regions;
        for(const auto& start : compatible_cavities)
        {
            std::vector<int> path;
            std::unordered_set<int> visited;
            std::function<void(cavity)> dfs = [&](cavity current) 
            {
                visited.insert(current.get_ID());
                path.push_back(current.get_ID());
                if (path.size() == cable.size()) 
                {
                    std::vector<int> sorted_path = path;
                    sort(sorted_path.begin(), sorted_path.end());
                    std::string key;
                    for (int id : sorted_path) 
                        key += std::to_string(id) + ",";
                    if (!seen.count(key)) 
                    {
                        seen.insert(key);
                        
                        std::vector<std::pair<int, int>> segments;
                        for (size_t i = 0; i < sorted_path.size(); ++i) 
                            for (size_t j = i + 1; j < sorted_path.size(); ++j) 
                                segments.emplace_back(sorted_path[i], sorted_path[j]);
                        regions.push_back({sorted_path, segments});
                    }
                    
                    visited.erase(current.get_ID());
                    path.pop_back();
                    return;
                }

                auto adj_list = _connector.get_adjacency_list();
                for (const auto& neighbor : adj_list[current.get_ID()]) 
                    if (neighbor.is_available() && !visited.count(neighbor.get_ID())) 
                        dfs(neighbor);

                visited.erase(current.get_ID());
                path.pop_back();
            };
            dfs(*start);
            
        }
        _region_table.push_back(regions);
        
    }
}

void cable_allocator::print_region_list()
{
    for(auto& list : _region_table)
    {
        int index = 1;
        std::print("possible choice for cable {}:\n",index);

        for(auto& item : list)
        {
            for(auto& cavity : item.get_list())
                std::print("{} ",cavity);
            std::print("\n");
        }
        
        index ++;
    }
}