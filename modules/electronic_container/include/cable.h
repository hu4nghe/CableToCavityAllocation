#pragma once

#include "wire.h"

#include <unordered_map>
#include <vector>

class cable
{
private:
    std::unordered_map<int, wire> _wires;
public:
    cable(std::vector<int> wire_gauges);
};