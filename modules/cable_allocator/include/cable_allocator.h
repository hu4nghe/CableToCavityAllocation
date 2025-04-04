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
    
    std::vector<std::vector<cable_region>> _region_table;
    std::vector<std::vector<cable_region>> _solutions;
    std::vector<cable>                     _cables;
    connector                              _connector;

public :

    // Dont initialize a void allocator !
    cable_allocator() = delete;

    /**
     * @brief Construct a cable allocator with cavity and cable list
     * 
     * @param cavities Connector's cavity list 
     * @param cables   Cable list
     */
    cable_allocator(const std::vector<cavity>& cavities, 
                    const std::vector<cable>&  cables);

private : 
    
    /**
     * @brief Generate all possible regions for each cable.
     * 
     */
    void generate_region_table();
    /**
     * @brief Allocate cables to the connector.
     * 
     */
    void allocate_cables();

public :
    // For debug use only -- print the calculation result
    void print_adjacency_list(){ _connector.print_list(); }
    void print_region_list();
    void print_solutions();
};