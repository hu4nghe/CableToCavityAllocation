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

connector::connector(const std::vector<cavity> &cavities) : 
    electronic_container_base(cavities)
{
    for(auto &[gauge, cavities] : _container)
    {
        //Calculer la distance entre les cavities, inutile si on connaît déjà ce chiffre.
        double min_distance = std::numeric_limits<double>::max();
        for(const auto& i : cavities)
            for(const auto& j : cavities)
                min_distance = 
                    j->distance(*i) < min_distance ? 
                        j->distance(*i) : 
                        min_distance;

        //build adjacency list
        const double epsilon = 0.3 * min_distance;
        for(const auto& i : cavities)
            for(const auto& j : cavities)
                if(std::abs(j->distance(*i) - min_distance) < epsilon)
                    _adjacency_list[i->get_ID()].insert(j->get_ID());
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
                    std::format("unavailable (connected to wire {})",
                                                      cavity->get_wire()->get_ID());
            std::print("Cavity {:<3}  {}\n", cavity->get_ID(), status_str);
        }
    }
}
