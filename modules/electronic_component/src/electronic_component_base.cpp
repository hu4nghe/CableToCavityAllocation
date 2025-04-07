#include "electronic_component_base.h"

electronic_component_base::electronic_component_base(const electronic_component_base &other) :
    _ID(other._ID),
    _gauge(other._gauge){}

electronic_component_base::electronic_component_base(electronic_component_base &&other) : 
    _ID(other._ID),
    _gauge(other._gauge){}

bool electronic_component_base::operator<(const electronic_component_base &other) const
{
    return _ID < other._ID;
}

electronic_component_base::electronic_component_base() :
    _ID(0),
    _gauge(AWG::AWGUnkown){}

electronic_component_base::electronic_component_base(const int &id,
                                                     const int &gauge) : 
    _ID(id),
    _gauge(static_cast<AWG>(gauge)){}

bool electronic_component_base::is_compatible(const electronic_component_base &other) const
{
    return other._gauge == _gauge;
}