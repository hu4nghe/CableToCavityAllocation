#include "cable.h"

cable::cable(int ID, std::vector<wire>&& wires):
    _ID(ID),
    electronic_container_base(std::move(wires)){}

bool cable::operator<(const cable &other) const
{
    return _ID < other._ID;
}