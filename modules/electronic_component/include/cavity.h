#pragma once

#include "AWG.h"

#include <utility>

class wire;

class cavity
{
private:
    const int                _ID;
    const AWG                _gauge;
    
    std::pair<double,double> _position;
    bool                     _availability;

public:
    cavity(int, int, double, double, bool);
    
    bool   operator==(const cavity&)  const;
    double distance(const cavity&)    const;
    bool   is_compatible(const wire&) const;

    int    get_ID() const { return _ID; }
};
