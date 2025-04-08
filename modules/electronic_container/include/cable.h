/**
 * @file cable.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief The class that represent a cable, who includes multiples wires
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_container_base.h"

class cable : public electronic_container_base<wire>
{
private: 
    int _ID;
public:
    cable(const int& ID, std::vector<wire>&& wires);

    bool operator<(const cable& other) const;

    int get_ID() const { return _ID; }

    auto size(AWG gauge) const { return _container.at(gauge).size(); }
};