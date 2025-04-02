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
    AWG _gauge;
public:
    cable(const std::vector<wire>& wires);

    AWG get_gauge() const { return _gauge; }
    std::size_t size() const { return _container.at(_gauge).size(); }
};