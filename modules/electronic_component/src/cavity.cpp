/**
 * @file cavity.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cavity class
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "cavity.h"
#include "wire.h"

#include <cmath>
#include <limits>

cavity::cavity(int ID, int cavity_gauge, double x, double y) :
    electronic_component_base(ID, cavity_gauge),
    _position(x, y){}

cavity::cavity(cavity&& other) : 
    electronic_component_base(std::move(other)),
    _position(std::move(other._position)){}

bool cavity::operator==(const cavity& others) const
{
    return others._ID == _ID;
}

bool cavity::operator<(const cavity& other) const
{
    return _ID < other._ID;
}

double cavity::distance(const cavity& others) const 
{
    if(*this == others) 
        return std::numeric_limits<double>::max();
    else 
        return sqrt(pow(others._position.first  - _position.first ,2) + 
                    pow(others._position.second - _position.second,2));
}

void cavity::connect(p_component<wire> target_wire) 
{
    disconnect();
    _connected_wire = target_wire;
}

void cavity::disconnect()
{
   _connected_wire.reset();
}

bool cavity::is_available() const
{
    return _connected_wire.expired();
}

std::shared_ptr<wire> cavity::get_wire() const
{ 
    return _connected_wire.lock(); 
}
