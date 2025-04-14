/**
 * @file cable_allocator.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Allocator who manages cable connections.
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 */
#pragma once

#include "cable_region.h"
#include "electronic_container.h"

class cable_allocator
{
private:

    std::map<cable, std::vector<cable_region>> _region_pool;
    connector                                  _connector;

public:

   
    cable_allocator() = delete;
    cable_allocator(const std::vector<std::tuple<int, int, double, double>>& cavities);
    void connect(std::map<int, int> connections);
    std::vector<std::tuple<int,int>> add_cable(int cable_ID, const std::vector<std::tuple<int, int>>& wires);
};