#include "wire.h"

wire::wire(int ID, int wire_gauge) :
electronic_component_base(std::move(ID), std::move(wire_gauge)){}
