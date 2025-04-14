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

#include <unordered_set>
#include <iostream>
#include <print>
#include <sstream>
#include <ranges>
#include <fstream>

cable_allocator::cable_allocator(std::vector<cavity> &&cavities) : _connector(std::move(cavities)) {}

bool cable_allocator::add_cable(cable new_cable)
{
    _region_pool[new_cable];

    for(const auto& cavity : _connector._container)
    {
        std::vector<std::pair<int, int>> path;
        std::unordered_set<int> visited;
        auto dfs =  
        [&](auto&& self,                 
            int cavity_ID,                 
            int wire_index) -> void
        {
            if(!_connector.is_available(cavity_ID) ||
               !wire_index >= new_cable.size()) return;

            auto wire   = new_cable._container[wire_index];
            auto cavity = _connector.get_Component(cavity_ID);
            
            // Check if the cavity is compatible with the wire
            if (!cavity->is_compatible(*wire)) return;
            // Log the searching path
            visited.insert(cavity_ID);
            path.emplace_back(wire->get_ID(), cavity_ID);

            // Save valid complete regions
            if (path.size() == new_cable.size())
                _region_pool.at(new_cable).emplace_back(path);
            else // Continue searching through available neighbors
                for (const auto& neighbor : _connector.get_adjacency_list(cavity_ID))
                    if (!visited.count(neighbor))
                        self(self, neighbor, wire_index + 1);
        
            // Backtrack
            visited.erase(cavity_ID);
            path.pop_back();
        };
        dfs(dfs, cavity->get_ID(), 0); 
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
            _connector.print_current_connector_status();
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
