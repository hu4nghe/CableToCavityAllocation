#pragma once

#include <vector>
#include <set>
#include <utility>

class cable_region
{
private :
    std::vector<int>             _cavity_index;
    std::set<std::pair<int,int>> _segments;
public:
    cable_region(const std::vector<int>&              index_list, 
                 const std::set<std::pair<int,int>>&  segments);

    bool operator==(const cable_region& other) noexcept;
    
    auto get_list() const { return _cavity_index; };
};