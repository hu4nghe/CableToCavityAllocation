/**
 * @file connector.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the connector class.
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "connector.h"

#include <print>
#include <ranges>

connector::connector(std::vector<cavity>&& cavities) : 
    electronic_container_base(std::move(cavities))
{
    build_adjacency_list();
}

void connector::build_adjacency_list()
{
    // Group cavities by gauge
    std::map<AWG, std::vector<p_component<cavity>>> gauge_map;
    for (const auto& cavity : _container)
        gauge_map[cavity->get_gauge()].push_back(cavity);

    // Store minimum distances for each gauge group internally
    std::map<AWG, double> intra_group_min_distances;
    
    // Store minimum distances between different gauge groups
    std::map<std::pair<AWG, AWG>, double> inter_group_min_distances;

    // Calculate minimum distances within each gauge group
    for (const auto& [gauge, cavities] : gauge_map) 
    {
        double min_distance = std::numeric_limits<double>::max();
        for (const auto& [idx, i] : std::views::enumerate(cavities))
            for (const auto& j : cavities | std::views::drop(idx + 1))
                intra_group_min_distances[gauge] = std::min(min_distance, i->distance(*j));
    }

    // Calculate minimum distances between each pair of different gauge groups
    for (const auto& [idx, i] : std::views::enumerate(gauge_map)) 
    {
        for (const auto& j : gauge_map | std::views::drop(idx + 1)) 
        {
            double min_distance = std::numeric_limits<double>::max();
            for (const auto& cavity1 : i.second) 
                for (const auto& cavity2 : j.second) 
                    min_distance = std::min(min_distance, cavity1->distance(*cavity2));

            // Store distances for both combinations of gauges
            inter_group_min_distances[{i.first, j.first}] = min_distance;
            inter_group_min_distances[{j.first, i.first}] = min_distance;
        }
    }

    // Build adjacency list
    for (const auto& i : _container) 
        for (const auto& j : _container) 
            if (i != j) 
            {
                double current_distance = i->distance(*j);
                
                if (i->is_compatible(*j)) 
                {
                    // Same gauge - use intra-group distance
                    double min_distance = intra_group_min_distances[i->get_gauge()];
                    double epsilon = 0.1 * min_distance;
                    if (std::abs(current_distance - min_distance) < epsilon) 
                        _adjacency_list[i->get_ID()].insert(j->get_ID());
                } 
                else 
                {
                    // Different gauges - use inter-group distance
                    double min_distance = inter_group_min_distances[{i->get_gauge(), j->get_gauge()}];
                    double epsilon = 0.1 * min_distance;
                    
                    if (std::abs(current_distance - min_distance) < epsilon) 
                        _adjacency_list[i->get_ID()].insert(j->get_ID());
                }
            }
}

std::vector<p_component<cavity>> connector::get_compatible_cavitiy_list(AWG gauge)
{
    std::vector<p_component<cavity>> compatible_cavities;
    for (const auto& cavity : _container)
        if (cavity->get_gauge() == gauge)
            compatible_cavities.push_back(cavity);
    return compatible_cavities;
}

std::set<int> connector::get_adjacency_list(const int &ID) const
{ 
    return _adjacency_list.at(ID);
} 

std::set<int> connector::get_unavailable_index_pool(AWG gauge) const
{
    std::set<int> occupied_cavity_index_pool;
    for (const auto& cavity : _container)
        if (cavity->get_gauge() == gauge && !cavity->is_available())
            occupied_cavity_index_pool.insert(cavity->get_ID());
    return occupied_cavity_index_pool;
}

bool connector::is_available(const int &ID)
{ 
    return get_Component(ID)->is_available(); 
}

void connector::print_adjacency_list() const
{
    for (const auto& [cavity_id, neighbors] : _adjacency_list)
    {
        std::print("Cavity {} is adjacent to: ", cavity_id);
        for (const auto& neighbor_id : neighbors)
            std::print("{} ", neighbor_id);
        std::print("\n");
    }
}

void connector::print_current_connector_status() const
{
    for(const auto cavity : _container)
    {
        auto status_str = 
            cavity->is_available() ? 
                std::format("available") :                                          
                std::format("unavailable (connected to wire {})", cavity->get_wire()->get_ID());
        std::print("Cavity {:<3}  {}\n", cavity->get_ID(), status_str);
    }
    
}
