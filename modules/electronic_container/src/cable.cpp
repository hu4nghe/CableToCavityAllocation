#include "cable.h"
cable::cable(const int &ID, const std::vector<wire>& wires):
    _ID(ID),
    electronic_container_base(wires){}
