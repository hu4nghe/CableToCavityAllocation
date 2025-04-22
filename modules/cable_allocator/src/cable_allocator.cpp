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
#include <algorithm>

cable_allocator::cable_allocator(const std::vector<std::tuple<int, int, double, double>>& cavity_data) :
    _connector(cavity_data){}

bool cable_allocator::add_cable(cable new_cable)
{
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
            if(!wire_index >= new_cable.size()) return; //wire index is out of range
            auto current_wire     = new_cable._container[wire_index];
            auto current_cavity = _connector.get_Component(cavity_ID);
            if(current_cavity->status()) return; // Cavity is already occupied
            if (!current_cavity->is_compatible(*current_wire)) return; // cavity not compatible

            // Log the searching path
            visited_cavity_indices.insert(cavity_ID);
            dfs_path.emplace_back(current_wire->get_ID(), cavity_ID);

            
            if (dfs_path.size() == new_cable.size()) // Save valid complete regions
                _region_pool.at(new_cable).emplace_back(dfs_path,_connector);
            else // Continue searching through available neighbors
                for (const auto& neighbor : _connector.get_adjacency_list(cavity_ID))
                    if (!visited_cavity_indices.count(neighbor))
                        self(self, neighbor, wire_index + 1);

            // Backtrack
            visited_cavity_indices.erase(cavity_ID);
            dfs_path.pop_back();
        };
        dfs(dfs, cavity_head->get_ID(), 0); 
    }
    std::ranges::sort(_region_pool[new_cable], {}, &cable_region::get_score);

    return !_region_pool[new_cable].empty();
}

void cable_allocator::connect(int cable_ID, int allocation)
{
    auto iter_cable = std::ranges::find(_region_pool, cable_ID, &cable::get_ID);
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
