#include <vector>
#include <tuple>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <ranges>
#include <tuple>

#include "graphic_tools.h"
#include "delaunay.h"

auto super_triangle(const std::vector<point>& points) 
{
    auto [min_x, max_x] = std::ranges::minmax(points | std::views::transform(&point::x));
    auto [min_y, max_y] = std::ranges::minmax(points | std::views::transform(&point::y));

    double avg_x = (min_x + max_x) / 2.0;

    const point p1(0, avg_x, max_y);
    const point p2(0, max_x, min_y);
    double k = p1.slope(p2);

    const point a(-1, avg_x,                               max_y - k * avg_x);
    const point b(-2, max_x + (min_y - max_y - 1) / k + 1, min_y - 1);
    const point c(-3, 2 * avg_x - b.x,                     min_y - 1); 

    return std::tuple(a, b, c);
}

std::vector<triangle> delaunayTriangulate(std::vector<point>& points) 
{
    if(points.size() <= 3) 
        throw std::invalid_argument("At least 4 points are required for triangulation.");

    std::vector<triangle> all_triangles;
    auto [p1, p2, p3] = super_triangle(points);
    all_triangles.emplace_back(p1, p2, p3);

    
    for (const auto& p : points) 
    {
        std::set<edge> polygon;
        all_triangles.erase(std::remove_if (all_triangles.begin(), 
                                            all_triangles.end(),
                                            [&](const triangle& tri) 
                                            {
                                                if (tri.circumCircle().contains(p)) 
                                                {
                                                    edge e1{tri.a, tri.b}, 
                                                         e2{tri.b, tri.c}, 
                                                         e3{tri.c, tri.a};
                                                    for (const auto& e : {e1, e2, e3}) 
                                                        if (polygon.count(e)) polygon.erase(e);
                                                        else polygon.insert(e);
                                                    return true;
                                                }
                                            else return false;
                                            }), 
                            all_triangles.end());
        //construct new triangles with current point and edges.                                
        for (const auto& e : polygon) 
            all_triangles.push_back({e.a, e.b, p});
        
    }

    // Remove triangles that contain any of the super triangle vertices.
    all_triangles.erase(std::remove_if(all_triangles.begin(), 
                                       all_triangles.end(), 
                                       [&](const triangle& tri) 
                                       {
                                            return tri.containsVertex(p1) || 
                                                   tri.containsVertex(p2) || 
                                                   tri.containsVertex(p3);
                                       }), 
                        all_triangles.end());


    return all_triangles;
}

auto build_adjacency_list(const std::vector<triangle>& triangles) 
{
    std::unordered_map<int, std::set<int>> adjacency_list;
    for (const auto& tri : triangles) 
    {
        int ids[3] = {tri.a.id, tri.b.id, tri.c.id};
        for (int i = 0; i < 3; ++i) 
            for (int j = 0; j < 3; ++j) 
                if (i != j) 
                    adjacency_list[ids[i]].insert(ids[j]);
    }

    std::unordered_map<int, std::vector<int>> adjacency;
    for (auto& [key, value] : adjacency_list) 
        adjacency[key] = std::vector<int>(value.begin(), value.end());
    return adjacency;
}

std::unordered_map<int, std::vector<int>> delaunay_triangulation(const std::vector<std::tuple<int, int, double, double>>& input) {
    std::vector<point> points;
    for (auto& [id, _, x, y] : input) 
        points.push_back(point{id, x, y});
    
    std::vector<triangle> triangles = delaunayTriangulate(points);
    return build_adjacency_list(triangles);
}
