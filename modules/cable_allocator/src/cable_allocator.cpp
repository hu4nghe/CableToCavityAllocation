/**
 * @file cable_allocator.cpp
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocator class.          
 * @version 1.0
 * @date 2025-04-02
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#include "cable_allocator.h"

#include <unordered_set>
#include <functional>
#include <numeric>

// Headers for debug use output only, to remove before release.
#include <print>
#include <ranges>
#include <fstream>
#include <filesystem>
#include <iostream>

cable_allocator::cable_allocator(std::vector<cavity>&& cavities) :
    _connector(std::move(cavities)){}

bool cable_allocator::add_cable(cable new_cable)
{
    _region_pool[new_cable];
 
    for(const auto& [gauge, wires] : new_cable._container)
    {       
        for (const auto& compatible_cavity : _connector.get_compatible_cavitiy_list(gauge))
        {
            std::vector<std::pair<int, int>> path;
            std::unordered_set<int> visited;

            auto dfs =             
            [&](auto&& self,                 
                int cavity_ID,                 
                int wire_index) -> void
            {
                if (!_connector.is_available(cavity_ID)) return;

                // Log the cavity_ID path
                auto wire_ID = wires[wire_index]->get_ID();
                visited.insert(cavity_ID);
                path.emplace_back(wire_ID, cavity_ID);

                // Save valid complete regions
                if (path.size() == new_cable.size(gauge))
                    _region_pool.at(new_cable).emplace_back(new_cable.get_ID(), gauge, path);
                
                else // Continue searching through available neighbors
                    for (const auto& neighbor : _connector.get_adjacency_list(cavity_ID))
                        if (_connector.is_available(neighbor) && !visited.count(neighbor))
                            self(self, neighbor, wire_index + 1);
                
                // Backtrack
                visited.erase(cavity_ID);
                path.pop_back();
            };
            // Start DFS from the compatible cavity
            dfs(dfs, compatible_cavity->get_ID(), 0);
        }
    }

    return finalize_allocation(new_cable);
}

bool cable_allocator::finalize_allocation(const cable& new_cable)
{
    const auto& valid_allocations = _region_pool.at(new_cable);

    if (valid_allocations.empty())
    {
        std::print("No valid allocation found for cable {}.\n", new_cable.get_ID());
        _region_pool.erase(new_cable);
        return false;
    }

    std::print("Possible choices for cable ({}):\n", new_cable.get_ID());
    for (const auto& [i, allocation] : std::views::enumerate(valid_allocations))
    {
        std::print("Allocation {}:\n", i + 1);
        for (const auto& [wire, cavity] : allocation.get_layout())
        {
            std::print("Wire {} -> Cavity {}\n", wire, cavity);
        }
        std::print("\n");
    }

    int choice = input(0, valid_allocations.size(), "Choose an allocation to continue.");
    std::print("Cable added with allocation {}.\n", choice);

    connect(valid_allocations[choice - 1].get_layout());
    return true;
}

void cable_allocator::connect(std::map<int, int> connections)
{
    for(const auto& [wire_idx, cavity_idx] : connections)
        for(auto& [cable, _] : _region_pool)
            _connector.get_Component(cavity_idx)->connect(cable.get_Component(wire_idx));
}

void cable_allocator::console_interaction()
{
    int wire_idx = 1;
    int cable_idx = 1;
    while(true)
    {
        std::vector<wire> wires;
        /*int gauge = 0;
        std::print("Please specify AWG of cable : \n");
        std::cin>>gauge;*/
        auto msg = std::format("Please specify the number of wires");
        int nb_wires = input(0, size(), msg);
        for(int i = 0; i < nb_wires; i++)
            wires.emplace_back(wire_idx++,22);
        
        cable cab(cable_idx++,std::move(wires));
        if(add_cable(cab))
            _connector.print_current_connector_status();
        else 
        {
            cable_idx--;
            wire_idx -= nb_wires;
        }
    }
}
int cable_allocator::input(int lower, int upper, const std::string& msg) const
{
    std::print("{}\n", msg);
    int input = 0;
    while(true)
    {
        if(std::cin >> input)
            if(input > lower && input < upper) 
                return input;
            else
                std::print("Value out of range. Try again.\n");
        else  
            std::print("Invalid input, try again.\n");
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

size_t cable_allocator::size() const
{
    return std::accumulate(_connector._container.begin(), 
                           _connector._container.end(), 
                           0,
                           [](size_t total, const auto& pair) 
                           {
                               return total + std::count_if(pair.second.begin(), 
                                                            pair.second.end(),
                                                            [](const auto& cavity) 
                                                            {
                                                                return cavity->is_available();
                                                            });
                           });
}

void cable_allocator::print_adjacency_list() const
{
    _connector.print_adjacency_list();
}
