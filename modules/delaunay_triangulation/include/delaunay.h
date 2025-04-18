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

std::unordered_map<int, std::vector<int>> delaunay_triangulation(const std::vector<std::tuple<int, int, double, double>>& input);