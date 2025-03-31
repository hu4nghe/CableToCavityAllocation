#pragma once

#include "AWG.h"

#include <utility>

class Wire;

class Cavity
{
private:
    const int                _ID;
    const AWG                _gauge;
    
    std::pair<double,double> _position;
    bool                     _availability;

public:
    Cavity(int, int, double, double, bool);
    
    bool   operator==(const Cavity&)  const;
    double distance(const Cavity&)    const;
    bool   is_compatible(const Wire&) const;

    int    get_ID() const { return _ID; }
};
