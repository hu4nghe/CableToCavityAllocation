#pragma once

#include "ElecUtility.h"

class Cable;

class Wire
{
private:
    const AWG    _gauge = AWG::AWGUnkown;
    const Cable* _parent;
public:
    Wire() = delete;
    Wire(const std::uint8_t& wire_gauge, const Cable* parent);

    const AWG get_gauge() const { return _gauge; }
};
