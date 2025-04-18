/**
 * @file connector.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the connector class.
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "connector.h"
#include "delaunay.h"

#include <map>
#include <set>

#include <print>
#include <ranges>
connector::connector(const std::vector<std::tuple<int, int, double, double>> &cavity_data) :
    electronic_container_base<cavity>(cavity_data),
    _adjacency_list(build_adjacency_list(cavity_data)) {}


void connector::print_adjacency_list() const
{
    for (const auto& [cavity_id, neighbors] : _adjacency_list)
    {
        std::print("Cavity {} is adjacent to: ", cavity_id);
        for (const auto& neighbor_id : neighbors)
            std::print("{} ", neighbor_id);
        std::print("\n");
    }
}

void connector::print_current_connector_status() const
{
    for(const auto cavity : _container)
    {
        auto status = cavity->status();
        auto text   = status ? 
            std::format("Available") : 
            std::format("Occupied by Cable {}", status);
        std::print("Cavity {}: {}\n", cavity->get_ID(), text);
    }
}
