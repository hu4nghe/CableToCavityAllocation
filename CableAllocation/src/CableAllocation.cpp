/**
 * 28/03/2025
 * HHG10 
 * Un algorithme pour trouver tous les solotion possibles d'allocation des cables aux cavités
 * 
 */
#include "CableAllocation.h"

#include "Cavity.h"
#include "Cable.h"

#include <vector>
#include <unordered_map>
#include <limits>
#include <cmath>

struct cable_region
{
    std::vector<int> _cavities;
    std::vector<std::pair<int, int>> _segments;
};

std::unordered_map<int, std::vector<int>> build_adjacency_list(const std::vector<Cavity> cavities)
{
    std::unordered_map<int, std::vector<int>> adj_list;

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
    

    const double epsilon = 1e-5;

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
        adj_list[i.get_ID()] = neighbors;
    }

    return adj_list;
}