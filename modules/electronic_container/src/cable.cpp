#include "cable.h"

cable::cable(std::vector<int> wire_gauges)
{
    for(int i = 0; i < wire_gauges.size(); i++)
        _wires.insert(std::pair<int, wire>(i, wire(wire_gauges[i])));
}