#pragma once

#include "Wire.h"

#include <unordered_map>
#include <vector>

class Cable
{
private:
    std::unordered_map<int, Wire> _wires;
public:
    Cable(std::vector<int> wire_gauges);
};