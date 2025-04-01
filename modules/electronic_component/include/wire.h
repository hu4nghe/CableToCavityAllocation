#pragma once

#include "AWG.h"

class cable;

class wire
{
private:
    const AWG    _gauge = AWG::AWGUnkown;
    
public:
    wire() = delete;
    wire(const int& wire_gauge);

    const AWG get_gauge() const { return _gauge; }
};
