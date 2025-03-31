#include "Wire.h"

Wire::Wire(const int& wire_gauge, const Cable *parent):
    _gauge(static_cast<AWG>(wire_gauge)),
    _parent(parent){}