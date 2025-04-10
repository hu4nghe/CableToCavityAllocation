/**
 * @file connector.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a connector, who includes multiples cavities.
 * @version 1.0
 * @date 2025-04-02
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "connector.h"

#include <print>

connector::connector(std::vector<cavity>&& cavities) : 
    electronic_container_base(std::move(cavities))
{
    build_adjacency_list();
}

void connector::build_adjacency_list()
{
    // Calculate the minimum distance between all cavities
    double min_distance = std::numeric_limits<double>::max();
    for (const auto& i : _container)
        for (const auto& j : _container)
            if (i != j)
                min_distance = std::min(min_distance, i->distance(*j));
            
    // Build the adjacency list with a tolerance.
    const double epsilon = 0.3 * min_distance;
    for (const auto& i : _container)
        for (const auto& j : _container)
            if (i != j)
                if (std::abs(i->distance(*j) - min_distance) < epsilon)
                    _adjacency_list[i->get_ID()].insert(j->get_ID());
}

std::vector<p_component<cavity>> connector::get_compatible_cavitiy_list(AWG gauge)
{
    std::vector<p_component<cavity>> compatible_cavities;
    for (const auto& cavity : _container)
        if (cavity->get_gauge() == gauge)
            compatible_cavities.push_back(cavity);
    return compatible_cavities;
}

std::set<int> connector::get_unavailable_index_pool(AWG gauge) const
{
    std::set<int> occupied_cavity_index_pool;
    for (const auto& cavity : _container)
        if (cavity->get_gauge() == gauge && !cavity->is_available())
            occupied_cavity_index_pool.insert(cavity->get_ID());
    return occupied_cavity_index_pool;
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
