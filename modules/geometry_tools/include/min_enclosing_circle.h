/**
 * @file min_enclosing_circle.h
 * @author HUANG He (he.huang@utt.fr)
 * @brief
 * This file declares a function that use welzl algorithm to calculate radius of min enclosing circle.
 * @version 1.1
 * @date 2025-04-22
 * 
 */
#include <vector>
#include <utility>

namespace geo_tools
{
    double calculate_min_enclosing_circle_radius(const std::vector<std::pair<double, double>>& coords);
}