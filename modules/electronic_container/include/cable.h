/**
 * @file cable.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * The class that represent a cable, who includes multiples wires
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#pragma once

#include "electronic_container_base.h"

class cable : public electronic_container_base<wire>
{
private: 

    int _ID;

public:
  
    /**
     * @brief Construct a new cable object
     * 
     * @param ID The ID of the cable    
     * @param wires Vector of all wires of current cable.       
     */
    cable(int ID, std::vector<wire>&& wires);

    bool add_wires(const std::vector<std::tuple<int, int>>& wires);
     
    /**
     * @brief Construct a new cable object
     * 
     * @param ID The ID of the cable    
     * @param wires Vector of all wires of current cable.       
     */
    bool operator<(const cable& other) const;

    /**
     * @brief Get the ID of the cable
     * 
     * @return The ID of the cable
     */
    auto get_ID() const { return _ID; }

    /**
     * @brief Get the size of the cable
     * 
     * @return The size of the cable
     */
    auto size() const { return _container.size(); }
};