/**
 * @file connector.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief The class that represent a cable, who includes multiples cavities
 * @version 1.0
 * @date 2025-04-01
 * 
 * @copyright Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_component.h"

#include "electronic_container_base.h"

#include <set>

class connector : public electronic_container_base<cavity>
{
private:
    std::map<int, std::set<cavity>> _adjacency_list;
public:
    connector(const std::vector<p_component<cavity>>& cavities);

    //debug functions
    void print_list() const;
};