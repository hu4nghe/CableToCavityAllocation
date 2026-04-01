/**
 * @file cable.cpp
 * @author
 * HUANG He (he.huang.intern@3ds.com)
 * @brief
 * Implementation of the cable class.
 * @version 2.0
 * @date 2025-07-09
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#include "cable.h"

#include <ranges>
#include <algorithm>
#include <stdexcept>

namespace
{
    // Keep only high-quality candidates to reduce both memory and UI noise.
    constexpr std::size_t kMaxCandidateAllocations = 20;
    constexpr double      kScorePruneFactor        = 1.8;
}

bool cable::generate_allocations(int mode)
{
    if (_container.empty()) return false; // No wires to allocate
    if(auto sp_connector = _wp_connector.lock())
    {
        _allocations.clear();

        auto try_store_candidate = [&](const std::vector<int>& visited)
        {
            cable_allocation candidate(visited, sp_connector);

            if (!_allocations.empty())
            {
                const double best_score = _allocations.begin()->get_score().combined();
                const double cand_score = candidate.get_score().combined();

                // Reject candidates that are much worse than the current best.
                if (cand_score > best_score * kScorePruneFactor)
                    return;
            }

            _allocations.emplace(std::move(candidate));

            // Keep only top-k candidates (set is already sorted best -> worst).
            while (_allocations.size() > kMaxCandidateAllocations)
                _allocations.erase(std::prev(_allocations.end()));

            // Tighten the set further when a new best appears.
            if (!_allocations.empty())
            {
                const double new_best = _allocations.begin()->get_score().combined();
                while (!_allocations.empty())
                {
                    auto worst_it = std::prev(_allocations.end());
                    if (worst_it->get_score().combined() <= new_best * kScorePruneFactor)
                        break;
                    _allocations.erase(worst_it);
                }
            }
        };

        auto define_searching_range = 
            [&]()
            {
                if (mode == 1)
                    // Search only the places near the allocated cavities.
                    return std::make_shared<connector>(
                        *sp_connector
                        // Find all allocated cavities.
                        | std::views::filter(   
                            [&](const auto& obj)
                            {
                                return obj->status() != 0; 
                            })

                        // Get their neighbors.
                        | std::views::transform(
                            [&](const auto& obj)
                            { 
                                return sp_connector->get_adj_list(obj->get_ID()); 
                            })

                        // Flatten the result(neighbor's ID)
                        | std::views::join

                        // Retrive the cavity object by ID.
                        | std::views::transform(
                            [&](int id)
                            {
                                return sp_connector->get_component(id);
                            })
                            
                        // Build filter result(searching near the allocated cavities.)
                        | std::ranges::to<connector>());
            
                else 
                    return sp_connector;
            };
    
        auto searching_range = define_searching_range();

        for (const auto& path_head_cavity : *searching_range)
        {
            std::vector<int> visited_cavity_indices;
            
            auto dfs =  
            [&](auto&& self,                 
                int    cavity_ID,
                int    wire_index)
            {
                auto current_cavity = sp_connector->get_component(cavity_ID);
                if (current_cavity->status()) return; // Cavity is already occupied
                auto current_wire = _container[wire_index];
                if (!current_cavity->is_compatible(*current_wire)) return; // cavity not compatible
                
                // Log the searching path
                visited_cavity_indices.push_back(cavity_ID);
                
                if (visited_cavity_indices.size() == size()) // Save valid complete regions
                    try_store_candidate(visited_cavity_indices);
                
                else // Continue searching through available neighbors
                    for (const auto& neighbor : sp_connector->get_adj_list(cavity_ID))
                        if (!std::ranges::contains(visited_cavity_indices,neighbor))
                            self(self, neighbor, wire_index + 1);

                // Backtrack
                visited_cavity_indices.pop_back();
            };
            dfs(dfs, path_head_cavity->get_ID(), 0); 
        }
        return !_allocations.empty();
    }
    else throw std::runtime_error("connector is expired !"); 
}

void cable::add_wires(const std::vector<std::tuple<int, int>> &wires)
{
    auto wire_index = 0;
    for (const auto& [wire_gauge, num_wires] : wires)
        for (auto i = 0; i < num_wires; ++i)
            _container.emplace_back(std::make_shared<wire>(wire_index++, wire_gauge));
}

void cable::confirme_allocation(int current_cable_ID, int allocation_ID)
{
    auto iter = std::next(_allocations.begin(), allocation_ID);
    if (iter == _allocations.end()) 
        throw std::out_of_range("Invalid allocation ID.");
        
    auto layout = (*iter).get_layout();
    if (auto sp_connector = _wp_connector.lock())
        for (const auto& chosen_cavity_ID : layout)
            sp_connector->get_component(chosen_cavity_ID)->allocate_to_cable(current_cable_ID);
    
    _allocations.clear();
}