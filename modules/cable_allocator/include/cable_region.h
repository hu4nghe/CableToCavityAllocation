#pragma once

#include "electronic_component.h"
#include "cable.h"

#include <map>
#include <set>

class cable_region
{
private:

    std::map<int, int> _wire_layout;

public:

    /**
     * @brief Construct a new cable region object
     * 
     * @param cable_ID ID of the cable.
     * @param connections A vector of pairs representing wire-cavity connections.
     */
    cable_region(const std::vector<std::pair<int,int>>& connections);
    
    /**
     * @brief Compare two cable regions based on their cable ID and wire layout.
     * 
     * @param other The other cable region to compare with.
     * @return true if this cable region is less than the other, false otherwise.
     */
    bool operator<(const cable_region& other) const;
    
    /**
     * @brief Check if the cable region has any unavailable cavities.
     * 
     * @param unavailable_pool A set of unavailable cavity indices.
     * @return true if there are unavailable cavities, false otherwise.
     */
    bool has_unavailable_cavity(const std::set<int>& unavailable_pool) const; 

    /**
     * @brief Get the wire layout.
     * 
     * @return std::map<int, int> wire layout.
     */
    std::map<int, int> get_layout() const; 

   
};