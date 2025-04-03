#pragma once

#include "electronic_component_base.h"

#include <vector>
#include <set>
#include <utility>

class cable_region
{
private :
    std::set<int>                _cavity_index;
    std::set<std::pair<int,int>> _segments;
    AWG                          _gauge;
public:
    cable_region(const std::vector<int>&             index_list, 
                 const std::set<std::pair<int,int>>& segments,
                 const AWG&                          gauge);
    
    auto get_list()  const { return _cavity_index; };
    auto get_gauge() const { return _gauge; }


    bool has_unavailable_cavity(std::set<int> unavailable_pool) const;
};