/**
 * @file cable_allocator.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * @version 1.0
 * @date 2025-04-02
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#pragma once

#include "cable_region.h"
#include "electronic_container.h"
#include "electronic_component.h"

class cable_allocator
{
private :
    std::vector<std::vector<cable_region>>     _solutions;

    std::map<cable, std::vector<cable_region>> _region_pool;
    connector                                  _connector;

public :

    // Dont initialize a void allocator !
    cable_allocator() = delete;

    /**
     * @brief Construct a cable allocator with connector's cavity list
     * 
     * @param cavities Connector's cavity list 
     */
    cable_allocator(const std::vector<cavity>& cavities);
    
    void add_cable(cable new_cable);

private : 
    /**
     * @brief Allocate cables to the connector.
     * 
     */
    void allocate_cables();

    void connect(std::map<int, int> connections);
    

public :
    // For debug use only -- print the calculation result
    void print_adjacency_list(){ _connector.print_adjacency_list(); }
    void print_current_solutions();
};