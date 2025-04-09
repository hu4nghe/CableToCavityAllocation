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

    #include <tuple>

class cable_allocator
{
private :
    std::map<cable, std::vector<cable_region>> _region_pool;
    connector                                  _connector;
public :

    // Dont initialize a void allocator !
    cable_allocator() = delete;
    cable_allocator(std::vector<cavity>&& cavities);
    void console_intereaction();

private : 
    void connect(std::map<int, int> connections);
    bool add_cable(cable new_cable);
    int input(int lower, int upper, const std::string& msg) const;
    size_t size() const;
public :
    // For debug use only -- print the calculation result
    void print_adjacency_list(){ _connector.print_adjacency_list(); }    
};