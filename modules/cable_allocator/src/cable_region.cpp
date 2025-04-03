#include "cable_region.h"

cable_region::cable_region(const std::vector<int>& index_list, 
                           const std::set<std::pair<int, int>>& segments) :
    _cavity_index(index_list),
    _segments(_segments) {}