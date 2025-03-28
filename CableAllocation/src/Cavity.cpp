#include "Cavity.h"
#include <cmath>

Cavity::Cavity(int number,double x, double y, int gauge_size):
    _number(number),
    _position(x, y),
    _gauge(static_cast<AWG>(gauge_size)){}

inline double Cavity::distance(const Cavity &others)
{
    return sqrt(pow(others._position.first,  _position.first) + 
                pow(others._position.second, _position.second));
}

inline bool Cavity::isCompatible(const AWG& wire_gauge)
{
    return _gauge == wire_gauge;
}
