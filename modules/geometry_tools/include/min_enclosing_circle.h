/**
 * @file min_enclosing_circle.h
 * @author 
 * HUANG He (he.huang@utt.fr)
 * @brief
 * This file declares a function that use welzl algorithm to calculate radius of min enclosing circle.
 * @version 2.0
 * @date 2025-07-09
 * 
 */

#pragma onece

#include <vector>

namespace geo_tools
{
    /**
     * @brief 
     * Calculate min enclosing circle's radius.
     * 
     * @param point_set The point set.
     * @return double Radius of minimum encolsing circle of the point set.
     */
    double calculate_min_enclosing_circle_radius(const std::vector<std::pair<double, double>>& point_set);
}