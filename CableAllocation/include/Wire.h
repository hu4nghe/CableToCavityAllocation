#pragma once

#include "ElecUtility.h"

class Cable;

class Wire
{
private:
    AWG          _gauge;
    const Cable* _parent;
public:
    Wire() = default;
    Wire(const std::uint8_t& wire_gauge, const Cable* parent);
};
