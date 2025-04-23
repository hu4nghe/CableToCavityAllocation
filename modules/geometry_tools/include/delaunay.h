/**
 * @file delaunay.h
 * @author HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Delaunay triangulation header file.
 * @version 1.0
 * @date 2025-04-18 
 * @copyright 
 * Dassault Systemes 2025
 */
#include <vector>
#include <tuple>
#include <unordered_map>

namespace geo_tools
{
    std::unordered_map<int, std::vector<int>> build_adjacency_list(const std::vector<std::tuple<int, int, double, double>>& input);
}

