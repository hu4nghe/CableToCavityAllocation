#include "cable_region.h"


cable_region::cable_region(const int&              cable_ID,
                           const std::vector<int>& index_list, 
                           const AWG&              gauge) :
    _cable_ID(cable_ID),
    _cavity_index(std::set<int>(index_list.begin(),index_list.end())),
    _gauge(gauge){}

bool cable_region::has_unavailable_cavity(std::set<int> unavailable_pool) const 
{
    for(const auto& cavity_idx : _cavity_index)
        if(unavailable_pool.count(cavity_idx)) return true;
    
    return false;
}
