/**
 * @file connector.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a connector.
 * @version 1.4
 * @date 2025-04-25
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#pragma once

#include "electronic_container_base.h"
#include "delaunay.h"

#include <map>
#include <unordered_map>
#include <ranges>
#include <print>

class connector : public electronic_container_base<cavity>
{
private :

    std::unordered_map<int, std::vector<int>> _adjacency_list;

public :
    
    /**
     * @brief 
     * Default connector constructor.
     * 
     */
    connector() = default;

    /**
     * @brief 
     * Construct a new connector object.
     * 
     * @param cavity_data Cavity's ID, gauge, and coordinates.
     */
    connector(const std::vector<std::tuple<int, int, double, double>>& cavity_data) :
        electronic_container_base<cavity>(cavity_data),
        _adjacency_list(geo_tools::build_adjacency_list(cavity_data)) {}

    /**
     * @brief 
     * Get the adjacency list object.
     * 
     * @param ID The ID of cavity that we want to know his adjacent nodes.
     * @return A vector which contains all adjacent nodes.
     */
    const auto& get_adj_list(int ID) const { return _adjacency_list.at(ID); } 

    /**
     * @brief Get the a list of cavities's status.
     * 
     * @return vector<int> that logs the status of cavities : 0 if available, otherwise the connected cable's ID. 
     */
    auto get_status() const
    {
        return _container
            | std::views::transform([](const auto& c){return c->status();})  
            | std::ranges::to<std::vector>();
    }

    ///debug functions///

    /**
     * @brief 
     * print auto-generated adjacency list.
     * 
     */
    void print_adjacency_list() const
    {
        std::map<int, std::vector<int>> ordered_result(_adjacency_list.begin(),_adjacency_list.end());
        for (const auto& [cavity_ID, neighbors] : ordered_result)
        {
            std::print("Cavity {:0>2} is adjacent to: ", cavity_ID);
            for (const auto& neighbor_ID : neighbors)
                std::print("{:0>2} ", neighbor_ID);
            std::print("\n");
        }
    }
    
    /**
     * @brief 
     * print cavities and their status.
     * 
     */
    void print_current_connector_status() const
    {
        for (const auto cavity : _container)
        {
            auto status = cavity->status();
            auto text = status ? 
                            std::format("Occupied by Cable {:<2}", status) :
                            std::format("Available");            
            std::print("Cavity {:<2}: {}\n", cavity->get_ID(), text);
        }
    }
   
};