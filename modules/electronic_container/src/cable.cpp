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

cable::cable(int ID, std::vector<wire>&& wires) :
    electronic_container_base(std::move(wires)),
    _ID(ID){}

bool cable::operator<(const cable &other) const
{
    return _ID < other._ID;
}