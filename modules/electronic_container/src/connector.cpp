/**
 * @file connector.cpp
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * @version 1.0
 * @date 2025-04-02
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#include "connector.h"

#include <print>
#include <ranges>

connector::connector(std::vector<cavity>&& cavities) : 
    electronic_container_base(std::move(cavities))
{
    // Clear the existing adjacency list
    _adjacency_list.clear();

    // Flatten all cavities into a single vector with their gauge
    std::vector<std::pair<AWG, p_component<cavity>>> all_cavities;
    for (const auto& [gauge, cavities] : _container)
        for (const auto& cavity : cavities)
            all_cavities.emplace_back(gauge, cavity);

    // Calculate the minimum distance for each pair of gauges
    std::map<std::pair<AWG, AWG>, double> min_dists;
    for (const auto& [gauge1, cavities1] : _container)
        for (const auto& [gauge2, cavities2] : _container)
        {
            double min_dist = std::numeric_limits<double>::max();

            for (const auto& cavity1 : cavities1)
                for (const auto& cavity2 : cavities2)
                    if (cavity1 != cavity2)
                        min_dist = std::min(min_dist, cavity1->distance(*cavity2));
                    
            min_dists[{gauge1, gauge2}] = min_dist;
        }
    
    // Build the adjacency list with a tolerance (epsilon) for each pair of gauges
    for (const auto& [gauge1, cavities1] : _container)
        for (const auto& cavity1 : cavities1)
            for (const auto& [gauge2, cavities2] : _container)
                for (const auto& cavity2 : cavities2)
                    if (cavity1 != cavity2)
                    {
                        auto key = std::make_pair(gauge1, gauge2);
                        double epsilon = 0.3 * min_dists[key];
                        if (std::abs(cavity1->distance(*cavity2) - min_dists[key]) < epsilon)
                            _adjacency_list[cavity1->get_ID()].insert(cavity2->get_ID());
                    }
}

std::vector<p_component<cavity>> connector::get_compatible_cavitiy_list(AWG gauge)
{
    if(_container.contains(gauge)) return _container.at(gauge);        
    else return std::vector<p_component<cavity>>();
}

std::set<int> connector::get_unavailable_index_pool(AWG gauge) const
{
    std::set<int> occupied_cavity_index_pool;
    for(const auto& p_cavity :_container.at(gauge))
        if(!p_cavity->is_available())
            occupied_cavity_index_pool.insert(p_cavity->get_ID());

    return occupied_cavity_index_pool;
    
}

void connector::print_adjacency_list() const
{
    for(auto& i : _adjacency_list)
    {
        std::print("cavity {} is adjacent to : ",i.first);
        for(auto& j : i.second) 
            std::print("{} ",j);
        std::print("\n");
    }
}

void connector::print_current_connector_status() const
{
    for(const auto [gauge, cavities] : _container)
    {
        std::print("Gauge {} :\n",static_cast<int>(gauge));
        for(const auto& cavity : cavities)
        {
            auto status_str = 
                cavity->is_available() ? 
                    std::format("available") :                                          
                    std::format("unavailable (connected to wire {})", cavity->get_wire()->get_ID());
            std::print("Cavity {:<3}  {}\n", cavity->get_ID(), status_str);
        }
    }
}
