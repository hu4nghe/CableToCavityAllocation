/**
 * 28/03/2025
 * HHG10 
 * Un algorithme pour trouver tous les solotion possibles d'allocation des cables aux cavités
 * 
 */
#include "cable_allocator.h"

#include <limits>
#include <cmath>
#include <print>
#include <utility>

#include <unordered_map>
cable_allocator::cable_allocator(const std::vector<cavity>&& cavities,const std::vector<cable>&& cables)
    : _cavity(std::move(cavities))
{
    //Calculer la distance entre les cavities, inutile si on connaît déjà ce chiffre.
    double min_distance = std::numeric_limits<double>::max();
    for(const auto& i : cavities)
        for(const auto& j : cavities)
            min_distance = j.distance(i) < min_distance ? j.distance(i) : min_distance;

    //Trouver les cavités adjacentes 
    const double epsilon = 0.3 * min_distance;
    for(const auto& i : cavities)
        for(const auto& j : cavities)
            if(std::abs(j.distance(i) - min_distance) < epsilon)
                _adjacency_list[i.get_ID()].insert(j.get_ID());
}

void cable_allocator::print_list() const
{
    for(auto& i : _adjacency_list)
    {
        std::print("cavity {} is adjacent to : ",i.first);
        for(auto& j : i.second) 
            std::print("{} ",j);
        std::print("\n");
    }
}
