#include "cable.h"

cable::cable(int ID, std::vector<wire>&& wires):
    electronic_container_base(std::move(wires)),
    _ID(ID){}

bool cable::operator<(const cable &other) const
{
    return _ID < other._ID;
}