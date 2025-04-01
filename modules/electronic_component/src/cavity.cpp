#include "cavity.h"
#include "wire.h"

#include <cmath>
#include <limits>

cavity::cavity(int number, int gauge_size, double x, double y, bool is_available):
    _ID(number),
    _position(x, y),
    _gauge(static_cast<AWG>(gauge_size)),
    _availability(is_available){}

bool cavity::operator==(const cavity& others) const
{
    return others._ID == _ID;
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
