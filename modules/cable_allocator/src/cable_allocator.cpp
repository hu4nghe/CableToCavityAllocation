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
#include <memory>
/*
std::vector<p_component<cavity>> convert_to_shared_ptr_vector(const std::vector<cavity>& cavities) 
{
    std::vector<p_component<cavity>> result;
    for (auto& cavity : cavities) 
    {
        result.push_back(std::make_shared<cavity>(cavity));
    }
    return result;
}

cable_allocator::cable_allocator(const std::vector<cavity>& cavities):
    _connector(convert_to_shared_ptr_vector(cavities))
{
   
   
}*/

// Helper function implementation
std::vector<std::shared_ptr<cavity>> convert_to_shared_ptr_vector(const std::vector<cavity>& cavities) {
    std::vector<std::shared_ptr<cavity>> result;
    result.reserve(cavities.size());
    for (const auto& cav : cavities) {
        // Either use direct construction:
        result.emplace_back(new cavity(cav));
        // Or if cavity is copyable:
        // result.push_back(std::make_shared<cavity>(cav));
    }
    return result;
}

cable_allocator::cable_allocator(const std::vector<cavity>& cavities)
    : _connector(convert_to_shared_ptr_vector(cavities))
{
    // Constructor implementation
}