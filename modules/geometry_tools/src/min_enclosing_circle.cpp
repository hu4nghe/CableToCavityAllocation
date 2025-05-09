/**
 * @file min_enclosing_circle.cpp
 * @author 
 * HUANG He (he.huang@utt.fr)
 * @brief 
 * Implementation of min_enclosing_circle.h
 * @version 1.4
 * @date 2025-04-25
 * 
 */

#include <algorithm>
#include <random>
#include <ctime>
#include <ranges>

#include "geometry_tools_base.h"
#include "min_enclosing_circle.h"

using namespace geo_tools;

std::vector<point> points_init(const std::vector<std::pair<double, double>>& coords) 
{
    std::vector<point> pts;
    for (const auto& [i, coord] : std::views::enumerate(coords))
        pts.emplace_back(i, coord.first, coord.second);
    return pts;
}

circle make_circle_two_points(const point& a, const point& b) 
{
    point center(-1, (a.x + b.x) / 2.0, (a.y + b.y) / 2.0);
    return circle(center, center.distance(a));
}

circle make_circle_three_points(const point& a, const point& b, const point& c) 
{
    triangle tri(a, b, c);
    return tri.circum_circle();
}

circle welzl(std::vector<point>& P, std::vector<point> R, int n) 
{
    if (n == 0 || R.size() == 3) 
    {
        if (R.empty()) return circle(point(-1, 0, 0), 0);
        if (R.size() == 1) return circle(R[0], 0);
        if (R.size() == 2) return make_circle_two_points(R[0], R[1]);
        return make_circle_three_points(R[0], R[1], R[2]);
    }

    point p = P[n - 1];
    circle d = welzl(P, R, n - 1);

    if (d.contains(p)) return d;

    R.push_back(p);
    return welzl(P, R, n - 1);
}

double geo_tools::calculate_min_enclosing_circle_radius(const std::vector<std::pair<double, double>>& point_set)
{
    std::vector<point> points = points_init(point_set);
    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::shuffle(points.begin(), points.end(), rng);

    circle mec = welzl(points, {}, points.size());
    return mec.radius;
}