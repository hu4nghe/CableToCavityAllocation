#include "Cavity.h"
#include "Wire.h"

#include <cmath>
#include <limits>

Cavity::Cavity(int number, int gauge_size, double x, double y, bool is_available):
    _ID(number),
    _position(x, y),
    _gauge(static_cast<AWG>(gauge_size)),
    _availability(is_available){}

bool Cavity::operator==(const Cavity& others) const
{
    return others._ID == _ID;
}

double Cavity::distance(const Cavity &others) const 
{
    if(*this == others) return std::numeric_limits<double>::max();
    else return sqrt(pow(others._position.first  - _position.first ,2) + 
                     pow(others._position.second - _position.second,2));
}

bool Cavity::is_compatible(const Wire& wire) const 
{
    return _gauge == wire.get_gauge();
}
