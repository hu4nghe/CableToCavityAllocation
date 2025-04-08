#include "wire.h"

wire::wire(const int& id,  const int& wire_gauge) :
    electronic_component_base(std::move(id), std::move(wire_gauge)){}