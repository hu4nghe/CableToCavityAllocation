/**
 * @file connector.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a connector, who includes multiples cavities.
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include "cable.h"

#include <set>
#include <map>

class connector : public electronic_container_base<cavity>
{
private:

    std::map<int, std::set<int>> _adjacency_list;

public:
    /**
     * @brief Construct a new connector object
     * 
     * @param cavities Vector of all cavities of current connector.
     */
    connector(std::vector<cavity>&& cavities);

    void build_adjacency_list();

    /**
     * @brief Get the compatible cavitiy list object.
     * 
     * @param gauge cable gauge
     * @return a vector that contains shared_ptr point to the cavity.
     */
    std::vector<p_component<cavity>> get_compatible_cavitiy_list(AWG gauge);

    /**
     * @brief Get the adjacency list object.
     * 
     * @param ID The ID of cavity that we want to know his adjacent nodes.
     * @return A set which contains all adjacent nodes.
     */
    std::set<int> get_adjacency_list(const int& ID) const;

    /**
     * @brief Get a set wich contains the unavailable cavities(occupied or reserved)'s index.
     * 
     * @param gauge cavity gauge type.
     * @return set of index of unavailable cavities.
     */
    std::set<int> get_unavailable_index_pool() const;

    /**
     * @brief Check if the cavity is available.
     * 
     * @param ID The ID of cavity that we want to know if it is available.
     * @return true if the cavity is available.
     * @return false if the cavity is not available.
     */
    bool is_available(const int& ID);

    //debug functions
    /**
     * @brief print auto-generated adjacency list.
     * 
     */
    void print_adjacency_list() const;

    /**
     * @brief print cavities and their status.
     * 
     */
    void print_current_connector_status() const;

    auto size() const;
   
};