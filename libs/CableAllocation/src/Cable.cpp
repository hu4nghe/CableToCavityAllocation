#include "Cable.h"

Cable::Cable(std::vector<int> wire_gauges)
{
    for(int i = 0; i < wire_gauges.size(); i++)
        _wires.insert(std::pair<int, Wire>(i, Wire(wire_gauges[i], this)));
}