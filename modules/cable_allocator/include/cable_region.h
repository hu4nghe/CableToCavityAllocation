#pragma once

#include "electronic_component.h"
#include "cable.h"

#include <vector>
#include <map>
#include <set>
#include <utility>

class cable_region
{
private :
    int                _cable_ID;
    AWG                _gauge;
    std::map<int, int> _wire_layout;
public:
    cable_region(const int&                             cable_ID,
                 const AWG&                     gauge,
                 const std::vector<std::pair<int,int>>& index_list);
    
    bool operator<(const cable_region& other) const;
    
    auto get_ID()     const { return _cable_ID; }
    auto get_layout() const { return _wire_layout; };
    auto get_gauge()  const { return _gauge; }

    bool has_unavailable_cavity(const std::set<int>& unavailable_pool) const;
};