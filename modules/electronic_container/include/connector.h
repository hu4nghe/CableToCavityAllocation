/**
 * @file connector.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief The class that represent a cable, who includes multiples cavities
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_component.h"

#include "electronic_container_base.h"
#include "cable.h"

#include <set>

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
    auto get_adjacency_list(const int& ID) const { return _adjacency_list.at(ID);} 

    /**
     * @brief Get a set wich contains the unavailable cavities(occupied or reserved)'s index.
     * 
     * @param gauge cavity gauge type.
     * @return set of index of unavailable cavities.
     */
    std::set<int> get_unavailable_index_pool(AWG gauge) const;

    //debug functions
    /**
     * @brief print auto-generated adjacency list.
     * 
     */
    void print_adjacency_list() const;

    void print_current_connector_status() const;
   
};