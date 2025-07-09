/**
 * @file connector.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a connector.
 * @version 2.0
 * @date 2025-07-09
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
};