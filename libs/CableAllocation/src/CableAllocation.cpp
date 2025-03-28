/**
 * 28/03/2025
 * HHG10 
 * Un algorithme pour trouver tous les solotion possibles d'allocation des cables aux cavités
 * 
 */
#include "CableAllocation.h"

#include "Cavity.h"
#include "Cable.h"


#include <limits>
#include <cmath>

#include <iostream>

struct cable_region
{
    std::vector<int> _cavities;
    std::vector<std::pair<int, int>> _segments;
};

void cable_allocator::build_adjacency_list(const std::vector<Cavity> cavities)
{
    //Calculer la distance entre les cavities, inutile si on connaît déjà ce chiffre.
    double min_distance = std::numeric_limits<double>::max();
    for(const auto& i : cavities)
    {
        for(const auto& j : cavities)
        {
            if(i == j) 
                continue;
            else 
                min_distance = j.distance(i) < min_distance ? j.distance(i) : min_distance;
        }
    }

    const double epsilon = 0.05 * min_distance;

    for(const auto& i : cavities)
    {
        std::vector<int> neighbors;
        for(const auto& j : cavities)
        {
            if(i == j) 
                continue;
            else if(std::abs(j.distance(i) - min_distance) < epsilon)
                neighbors.push_back(j.get_ID());
        }
        auto ID = i.get_ID();
        _adjacency_list[i.get_ID()] = neighbors;
    }
}

void cable_allocator::print_list() const
{
    for(auto& i : _adjacency_list)
    {
        std::cout<<"Element "<<i.first<<" is adjacent to :\n";
        for(auto& j : i.second)
        {
            std::cout<<j<<"\n";
        }
    }
    std::cout<<std::endl;
}
