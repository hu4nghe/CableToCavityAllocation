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

#include <print>
#include <ranges>
connector::connector(const std::vector<std::tuple<int, int, double, double>> &cavity_data) :
    electronic_container_base<cavity>(cavity_data),
    _adjacency_list(delaunay::build_adjacency_list(cavity_data)) {}

double connector::distance(int i, int j) const
{
    auto iter_i = std::ranges::find(_container, i, &cavity::get_ID);
    auto iter_j = std::ranges::find(_container, j, &cavity::get_ID);
    if(iter_i != _container.end() && iter_j != _container.end())
        return (*iter_i)->distance(**iter_j);
    else
        throw std::invalid_argument("Invalid cavity ID(s) provided.");
}

void connector::print_adjacency_list() const
{
    for (const auto& [cavity_ID, neighbors] : _adjacency_list)
    {
        std::print("Cavity {} is adjacent to: ", cavity_ID);
        for (const auto& neighbor_ID : neighbors)
            std::print("{} ", neighbor_ID);
        std::print("\n");
    }
}

void connector::print_current_connector_status() const
{
    for(const auto cavity : _container)
    {
        auto status = cavity->status();
        auto text = status ? 
                                    std::format("Available") : 
                                    std::format("Occupied by Cable {}", status);
        std::print("Cavity {}: {}\n", cavity->get_ID(), text);
    }
}
