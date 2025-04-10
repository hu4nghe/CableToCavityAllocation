/**
 * @file electronic_component_base.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the electronic_component_base class
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "electronic_component_base.h"

electronic_component_base::electronic_component_base() : 
    _ID(0),
    _gauge(AWG::AWGUnkown){}

electronic_component_base::electronic_component_base(const int& ID, const int& gauge) : 
    _ID(ID),
    _gauge(static_cast<AWG>(gauge)){}

electronic_component_base::electronic_component_base(electronic_component_base&& other) : 
    _ID(other._ID),
    _gauge(other._gauge){}

bool electronic_component_base::operator<(const electronic_component_base &other) const
{
    return _ID < other._ID;
}

const AWG electronic_component_base::get_gauge() const
{
    return _gauge; 
}

const int electronic_component_base::get_ID() const
{
    return _ID;
}

bool electronic_component_base::is_compatible(const electronic_component_base &other) const
{
    return other._gauge == _gauge;
}