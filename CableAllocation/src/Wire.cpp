#include "Wire.h"

Wire::Wire(const std::uint8_t &wire_gauge, const Cable *parent):
    _gauge(static_cast<AWG>(wire_gauge)),
    _parent(parent){}