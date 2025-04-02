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
    
    //std::unordered_map<int, std::unordered_map<int,cable_region>> _region_table;
    connector _connector;

public :
    cable_allocator() = delete;
    cable_allocator(const std::vector<cavity>&);
    void print_list(){ _connector.print_list(); }

};