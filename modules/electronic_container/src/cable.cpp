#include "cable.h"
cable::cable(const std::vector<wire>& wires):
    electronic_container_base(wires)
{
    if(!_container.empty()) _gauge = AWG::AWG22;
}