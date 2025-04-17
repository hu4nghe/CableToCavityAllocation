/**
 * @file cable.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable class.
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "cable.h"

bool is_valid(const int awg_value)
{
    auto val = static_cast<AWG>(awg_value);
    switch (val) 
    {
        case AWG::AWGUnkown:
        case AWG::AWG8:
        case AWG::AWG10:
        case AWG::AWG12:
        case AWG::AWG16:
        case AWG::AWG20:
        case AWG::AWG22:
            return true;
        default:
            return false;
    }
}


cable::cable(int ID, std::vector<wire>&& wires) :
    electronic_container_base(std::move(wires)),
    _ID(ID){}

bool cable::add_wires(const std::vector<std::tuple<int, int>>& wires)
{
    for (const auto& [wire_gauge, num_wires] : wires)
    {
        if(is_valid(wire_gauge))
            for(auto i = 0; i < num_wires; ++i)
                _container.emplace_back(i, wire_gauge);
        else
            return false;
    }
    return true;    
}

bool cable::operator<(const cable &other) const
{
    return _ID < other._ID;
}