/**
 * @file delaunay.cpp
 * @author
 * HUANG He (he.huang@utt.fr)
 * @brief
 * Implementation of delaunay.h
 * @version 1.5
 * @date 2025-05-18
 *
 */

#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>

#include "delaunay.h"
#include "geometry_tools_base.h"

using namespace geo_tools;

auto super_triangle(const std::vector<point>& points)
{
    auto [min_x, max_x] = std::ranges::minmax(
        points | std::views::transform(&point::x));
    auto [min_y, max_y] = std::ranges::minmax(
        points | std::views::transform(&point::y));

    double      avg_x = (min_x + max_x) / 2.0;
    const point p1(0, avg_x, max_y);
    const point p2(0, max_x, min_y);
    double      k = p1.slope(p2);

    const point a(-1, avg_x, max_y - k * avg_x);
    const point b(
        -2,
        max_x + (min_y - max_y - 1) / k + 1,
        min_y - 1);
    const point c(-3, 2 * avg_x - b.x, min_y - 1);

    return std::tuple(a, b, c);
}

auto delaunay_triangulate(const std::vector<point>& points)
{
    if (points.size() <= 3)
        throw std::invalid_argument(
            "At least 4 points are required for triangulation.");

    // Construct a super triangle at first.
    auto [p1, p2, p3] = super_triangle(points);
    std::vector<triangle> all_triangles{triangle(p1, p2, p3)};

    for (const auto& p : points)
    {
        std::set<edge> polygon;
        std::erase_if(
            all_triangles,
            [&](const triangle& tri)
            {
                if (tri.circum_circle().contains(p))
                {
                    edge e1{tri.a, tri.b}, e2{tri.b, tri.c},
                        e3{tri.c, tri.a};
                    for (const auto& e : {e1, e2, e3})
                        if (!polygon.erase(e)) polygon.insert(e);
                    return true;
                }
                return false;
            });

        // construct new triangles with current point and edges.
        for (const auto& e : polygon)
            all_triangles.emplace_back(p, e);
    }

    // Remove triangles that contain any of the super triangle
    // vertices.
    std::erase_if(
        all_triangles,
        [&](const triangle& tri)
        {
            for (const auto& p : {p1, p2, p3})
                if (tri.containsVertex(p)) return true;
            return false;
        });

    return all_triangles;
}

auto build_adjacency_list_from_result(
    const std::vector<triangle>& triangles)
{
    std::unordered_map<int, std::set<int>> adjacency_set;

    for (const auto& tri : triangles)
        for (const auto& i : {tri.a.id, tri.b.id, tri.c.id})
            for (const auto& j : {tri.a.id, tri.b.id, tri.c.id})
                if (i != j) adjacency_set[i].insert(j);

    return adjacency_set |
           std::views::transform(
               [](auto&& pair)
               {
                   auto&& [key, value] = pair;
                   return std::pair{
                       key,
                       std::vector<int>(
                           value.begin(),
                           value.end())};
               }) |
           std::ranges::to<std::unordered_map>();
}

auto geo_tools::build_adjacency_list(
    const std::vector<std::tuple<
        int,
        int,
        double,
        double>>& point_data)
    -> std::unordered_map<
        int,
        std::vector<int>>
{
    return build_adjacency_list_from_result(delaunay_triangulate(
        point_data // convert point_data to a point vector
        | std::views::transform(
              [](auto&& t)
              {
                  auto&& [id, _, x, y] = t;
                  return point{id, x, y};
              }) |
        std::ranges::to<std::vector<point>>()));
}