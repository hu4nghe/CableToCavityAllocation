#pragma once

#include <vector>
#include <utility>

class cable_region
{
private :
    std::vector<int>                _cavity_index;
    std::vector<std::pair<int,int>> _segments;
public:
    cable_region(std::vector<int> index_list, std::vector<std::pair<int,int>> segments);
    bool operator==(const cable_region& other) noexcept;
    auto get_list() const { return _cavity_index; };
};