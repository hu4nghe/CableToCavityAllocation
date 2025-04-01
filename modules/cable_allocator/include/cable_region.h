#pragma once

#include <vector>
#include <utility>

class cable_region
{
private :
    std::vector<int>                _cavity_index;
    std::vector<std::pair<int,int>> _segments;
public:
    bool operator==(const cable_region& other) noexcept;
};