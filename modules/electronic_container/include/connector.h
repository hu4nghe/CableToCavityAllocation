/**
 * @file connector.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a connector, who includes multiples cavities.
 * @version 1.2
 * @date 2025-04-17
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include <unordered_map>

#include "electronic_container_base.h"

class connector : public electronic_container_base<cavity>
{
private:

    std::unordered_map<int, std::vector<int>> _adjacency_list;

public:
    
    connector(const std::vector<std::tuple<int, int, double, double>>& cavity_data); 

    /**
     * @brief Get the adjacency list object.
     * 
     * @param ID The ID of cavity that we want to know his adjacent nodes.
     * @return A set which contains all adjacent nodes.
     */
    std::vector<int> get_adjacency_list(const int& ID) const { return _adjacency_list.at(ID); } 

    double distance(int i, int j) const;

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
   
};