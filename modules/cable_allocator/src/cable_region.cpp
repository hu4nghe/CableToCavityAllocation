#include "cable_region.h"


cable_region::cable_region(const std::vector<int>&              index_list, 
                           const std::set<std::pair<int, int>>& segments,
                           const AWG&                           gauge) :
    _cavity_index(std::set<int>(index_list.begin(),index_list.end())),
    _segments(_segments),
    _gauge(gauge){}

bool cable_region::has_unavailable_cavity(std::set<int> unavailable_pool) const 
{
    for(const auto& cavity_idx : _cavity_index)
        if(unavailable_pool.count(cavity_idx)) return true;
    
    return false;
}
