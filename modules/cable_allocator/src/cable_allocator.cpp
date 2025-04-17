/**
 * @file cable_allocator.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocator class.          
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "cable_allocator.h"
#include "cavity.h"

#include <unordered_set>
#include <iostream>
#include <print>
#include <sstream>
#include <ranges>

cable_allocator::cable_allocator(std::vector<cavity>&& cavities) :
    _connector(std::move(cavities)){}

bool cable_allocator::add_cable(cable new_cable)
{
    bool add_cable_succeed = false;
    _region_pool[new_cable];

    for(const auto& cavity_head : _connector._container)
    {
        std::vector<std::pair<int, int>> dfs_path;
        std::unordered_set<int> visited_cavity_indices;
        std::pair<double, double> center;
        double radius{};
        
        auto dfs =  
        [&](auto&& self,                 
            int cavity_ID,                 
            int wire_index) -> void
        {
            if(!_connector.is_available(cavity_ID) || // Current cavity is not available 
               !wire_index >= new_cable.size())      // wire index is out of range
                return;

            auto current_wire   = new_cable._container[wire_index];
            auto current_cavity = _connector.get_Component(cavity_ID);
            
            // Check if the cavity is compatible with the wire
            if (!current_cavity->is_compatible(*current_wire)) return;
            // Log the searching path
            visited_cavity_indices.insert(cavity_ID);
            dfs_path.emplace_back(current_wire->get_ID(), cavity_ID);

            auto old_raius = radius;
            auto old_center = center;

            double max_dist{};
            std::pair<sp_component<cavity>, 
                      sp_component<cavity>> furtherst_cavity;
            for(const auto& [_, i] : dfs_path)
            {
                auto selected_cavity_i = _connector.get_Component(i);
                for(const auto& [_, j] : dfs_path)
                {
                    auto selected_cavity_j =_connector.get_Component(j);
                    double current_dist{};
                    if( i == j ) 
                        current_dist = 0;
                    else
                        current_dist = selected_cavity_i->distance(*selected_cavity_j);

                    if( current_dist >= max_dist)
                    {
                        max_dist = current_dist;
                        furtherst_cavity = std::make_pair(selected_cavity_i, selected_cavity_j);
                    }
                }
            }
            if(furtherst_cavity.first == furtherst_cavity.second) radius = 0;
            radius = furtherst_cavity.first->distance(*furtherst_cavity.second) / 2.0;
            center = furtherst_cavity.first->midpoint(*furtherst_cavity.second);
            
            // Save valid complete regions
            if (dfs_path.size() == new_cable.size())
                _region_pool.at(new_cable).emplace_back(dfs_path, radius);
            else // Continue searching through available neighbors
                for (const auto& neighbor : _connector.get_adjacency_list(cavity_ID))
                    if (!visited_cavity_indices.count(neighbor))
                        self(self, neighbor, wire_index + 1);
        
            // Backtrack
            visited_cavity_indices.erase(cavity_ID);
            dfs_path.pop_back();
            radius = old_raius;
            center = old_center;    
        };
        dfs(dfs, cavity_head->get_ID(), 0); 
    }
    
    std::sort(_region_pool[new_cable].begin(), 
              _region_pool[new_cable].end(), 
              [](const cable_region& a, const cable_region& b) 
              { return a.get_score() < b.get_score(); });


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
        auto score = allocation.get_score();
        //if (score >= 50) continue;
        std::print("Allocation {}: score : {}\n", i + 1,score);    
        for (const auto& [wire, cavity] : allocation.get_layout())
            std::print("Wire {} -> Cavity {}\n", wire, cavity);
        
        std::print("\n");
    }

    int choice = input(1, valid_allocations.size(), "Choose an allocation to continue.");

    connect(valid_allocations[choice - 1].get_layout());
    std::print("Cable added with allocation {}.\n", choice);
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

    while (true)
    {
        std::vector<wire> wires;
        std::string input_line;

        std::print("Enter groups of data (gauge number_of_wires), or type 'end' to finish:\n");
        
        while (true)
        {
            std::getline(std::cin, input_line);
            
            // Skip empty lines
            if (input_line.empty())
                continue;

            // Check if the user wants to end the input
            if (input_line == "end")
                break;

            // Parse the input line
            std::istringstream iss(input_line);
            int gauge, num_wires;
            if (!(iss >> gauge >> num_wires))
            {
                std::print("Invalid input. Please enter two integers (gauge number_of_wires) or 'end'.\n");
                
                continue;
            }

            // Add wires of the specified gauge
            for (int i = 0; i < num_wires; ++i)
                wires.emplace_back(wire_idx++, gauge);
            
        }

        // Create a cable with the specified wires
        cable cab(cable_idx++, std::move(wires));

        // Attempt to add the cable
        if (add_cable(cab))
        {
            _connector.print_current_connector_status();
        }
        else
        {
            std::print("Failed to add cable. Rolling back.\n");
            cable_idx--;
            wire_idx -= cab.size();
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
            if(input >= lower && input <= upper) 
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
    return std::count_if(_connector._container.begin(), 
                         _connector._container.end(),
                         [](const auto& cavity) 
                         {
                             return cavity->is_available();
                         });
}

void cable_allocator::print_adjacency_list() const
{
    _connector.print_adjacency_list();
}
