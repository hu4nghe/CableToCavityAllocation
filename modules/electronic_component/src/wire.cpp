#include "wire.h"

wire::wire(const int& wire_gauge):
    _gauge(static_cast<AWG>(wire_gauge)){}