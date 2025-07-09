/**
 * @file delaunay.h
 * @author 
 * HUANG He (he.huang@utt.fr)
 * @brief 
 * Delaunay triangulation header file.
 * @version 2.0
 * @date 2025-07-09
 * 
 */

#pragma once

#include <vector>
#include <tuple>
#include <unordered_map>

namespace geo_tools
{
    /**
     * @brief 
     * Build adjacency list for a point set in format point ID <-> adjacent point list.
     * 
     * @param cavity_data All 
     * @return std::unordered_map<int, std::vector<int>> Vector of lists.
     */
    auto build_adjacency_list(const std::vector<std::tuple<int, int, double, double>>& point_data) -> std::unordered_map<int, std::vector<int>>;
}