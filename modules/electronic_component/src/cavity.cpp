#include "cavity.h"
#include "wire.h"

#include <cmath>
#include <limits>


cavity::cavity(const int& id, 
               const int& cavity_gauge, 
               const double& x, 
               const double& y, 
               const bool& is_available):
    electronic_component_base(id, cavity_gauge),
    _position(x, y),
    _availability(is_available){}

bool cavity::operator==(const cavity& others) const
{
    return others._ID == _ID;
}

bool cavity::operator<(const cavity &other) const
{
    return _ID < other._ID;
}

double cavity::distance(const cavity &others) const 
{
    if(*this == others) return std::numeric_limits<double>::max();
    else return sqrt(pow(others._position.first  - _position.first ,2) + 
                     pow(others._position.second - _position.second,2));
}

bool cavity::is_compatible(const wire& wire) const 
{
    return _gauge == wire.get_gauge();
}
