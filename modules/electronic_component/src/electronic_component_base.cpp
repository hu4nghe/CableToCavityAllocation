#include "electronic_component_base.h"

#include <compare>

electronic_component_base::electronic_component_base(const int &id, 
                                                     const int &gauge):
    _ID(id), 
    _gauge(static_cast<AWG>(gauge)){}

