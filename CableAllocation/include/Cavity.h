#pragma once

#include "ElecUtility.h"

#include <utility>

class Wire;

class Cavity
{
private:
    const int                _ID;
    const AWG                _gauge;
    
    std::pair<double,double> _position;
    std::pair<int,double>    _neighbors;

    bool                     _availability;

public:
    Cavity(int, double, double, int, bool);
    
    bool   operator==(const Cavity&)  const;
    double distance(const Cavity&)    const;
    bool   is_compatible(const Wire&) const;

    int    get_ID() const { return _ID; }
};
