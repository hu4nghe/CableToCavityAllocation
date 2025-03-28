#pragma once

#include "ElecUtility.h"

#include <utility>

class Cavity
{
private:
    int                      _number;
    std::pair<double,double> _position;
    AWG                      _gauge;
public:
    Cavity(int, double, double, int);
    
    double distance(const Cavity&);
    bool   isCompatible(const AWG&);
};
