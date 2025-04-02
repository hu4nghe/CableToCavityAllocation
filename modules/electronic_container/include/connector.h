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
    /**
     * @brief Construct a new connector object
     * 
     * @param cavities Vector of all cavities of current connector.
     */
    connector(const std::vector<cavity>& cavities);

    //debug functions
    /**
     * @brief print auto-generated adjacency list.
     * 
     */
    void print_list() const;

private: //internal tools
    /**
     * @brief Convert a electronic_component_base vector into a p_component vector.
     *        The new vector will take the ownership of object vector.
     * 
     * @param cavities Cavity object vector.
     * @return Cavity Object shared_ptr vector.
     */
    std::vector<p_component<cavity>> convert_ptr_vector(const std::vector<cavity>& cavities);
};