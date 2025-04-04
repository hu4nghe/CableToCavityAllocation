#pragma once

#include "electronic_component.h"
#include "cable.h"

#include <vector>
#include <set>
#include <map>
#include <utility>

class cable_region
{
private :
    int                            _cable_ID;
    std::set<int>                  _cavity_index;
    AWG                            _gauge;
public:
    cable_region(const int&              cable_ID,
                 const std::vector<int>& index_list, 
                 const AWG&              gauge);
    
    auto get_list()  const { return _cavity_index; };
    auto get_gauge() const { return _gauge; }


    bool has_unavailable_cavity(std::set<int> unavailable_pool) const;
};