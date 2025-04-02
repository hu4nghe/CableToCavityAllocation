#include "cable_region.h"

cable_region::cable_region(std::vector<int> index_list, std::vector<std::pair<int, int>> segments) :
    _cavity_index(index_list),
    _segments(_segments)
{
}