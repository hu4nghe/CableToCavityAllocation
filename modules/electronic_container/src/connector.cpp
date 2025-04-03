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

connector::connector(const std::vector<cavity> &cavities) : 
    electronic_container_base(cavities)
{
    for(auto &gauge_type : _container)
    {
        //Calculer la distance entre les cavities, inutile si on connaît déjà ce chiffre.
        double min_distance = std::numeric_limits<double>::max();
        for(const auto& i : gauge_type.second)
            for(const auto& j : gauge_type.second)
               min_distance = j->distance(*i) < min_distance ? j->distance(*i) : min_distance;

        //build adjacency list
        const double epsilon = 0.3 * min_distance;
        for(const auto& i : gauge_type.second)
            for(const auto& j : gauge_type.second)
                if(std::abs(j->distance(*i) - min_distance) < epsilon)
                    _adjacency_list[i->get_ID()].insert(*j);
    }
}

std::vector<p_component<cavity>> connector::get_compatible_cavitiy_list(AWG gauge)
{
    if(_container.contains(gauge)) return _container.at(gauge);        
    else return std::vector<p_component<cavity>>();
}

void connector::print_list() const
{
    for(auto& i : _adjacency_list)
    {
        std::print("cavity {} is adjacent to : ",i.first);
        for(auto& j : i.second) 
            std::print("{} ",j.get_ID());
        std::print("\n");
    }
}