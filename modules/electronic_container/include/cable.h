/**
 * @file cable.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a cable, who includes multiples wires
 * @version 1.2
 * @date 2025-04-17
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_container_base.h"

class cable : public electronic_container_base<wire>
{
private: 

    int _ID;

public:

    cable(int ID) : _ID(ID) {}
    
    // For STL set/map compatibility
    auto operator<(const cable& other) const { return _ID < other._ID; }
    
    void add_wires(const std::vector<std::tuple<int, int>>& wires)
    {
        for (const auto& [wire_gauge, num_wires] : wires)
            for(auto i = 0; i < num_wires; ++i)
                _container.emplace_back(i, wire_gauge);
    }

    /// Getters
    auto get_ID() const { return _ID; }
    auto size()   const { return _container.size(); }
};