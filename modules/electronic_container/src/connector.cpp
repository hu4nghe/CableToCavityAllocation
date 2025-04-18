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
#include "delaunay.h"

#include <map>
#include <set>

#include <print>
#include <ranges>
connector::connector(const std::vector<std::tuple<int, int, double, double>> &cavity_data) :
    electronic_container_base<cavity>(cavity_data)
{
    _adjacency_list = delaunay_triangulation(cavity_data);

    /*
    // Group cavities by gauge
    std::map<AWG, std::vector<sp_component<cavity>>> gauge_map;
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
                        _adjacency_list[i->get_ID()].push_back(j->get_ID());
                } 
                else 
                {
                    // Different gauges - use inter-group distance
                    double min_distance = inter_group_min_distances[{i->get_gauge(), j->get_gauge()}];
                    double epsilon = 0.1 * min_distance;
                    
                    if (std::abs(current_distance - min_distance) < epsilon) 
                        _adjacency_list[i->get_ID()].push_back(j->get_ID());
                }
            }*/

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
        auto status = cavity->status();
        auto text   = status ? 
            std::format("Available") : 
            std::format("Occupied by Cable {}", status);
        std::print("Cavity {}: {}\n", cavity->get_ID(), text);
    }
}
