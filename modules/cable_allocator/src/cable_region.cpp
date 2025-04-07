#include "cable_region.h"

#include <ranges>


cable_region::cable_region(const int&                              cable_ID,
                           const AWG&                              gauge, 
                           const std::vector<std::pair<int, int>>& wire_cavity_map) :
    _cable_ID(cable_ID),
    _wire_layout(std::map<int, int>(wire_cavity_map.begin(),wire_cavity_map.end())),
    _gauge(gauge){}

bool cable_region::has_unavailable_cavity(const std::set<int>& unavailable_pool) const 
{
    for(const auto& cavity_index : std::views::values(_wire_layout))
        if(unavailable_pool.count(cavity_index)) return true;
    
    return false;
}