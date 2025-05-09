/**
 * @file geometry_tool_base.h
 * @author 
 * HUANG He (he.huang@utt.fr)
 * @brief
 * This file defines serveral basical structure for geometry calculations
 * @version 1.4
 * @date 2025-04-25
 *
 */

#pragma once
 
#include <cmath>
#include <stdexcept>
namespace geo_tools
{
    struct point
    {
    public:
        int id;
        double x, y;

        point() = default;
        point(int id, double x, double y) : id(id), x(x), y(y) {}

        bool operator==(const point& p) const { return id == p.id && x == p.x && y  == p.y; }
        bool operator!=(const point& p) const { return !(*this == p); }

        double distance(const point& p) const { return std::sqrt((x - p.x) * (x - p.x) + 
                                                                (y - p.y) * (y - p.y)); }
        double slope   (const point& p) const { return *this != p ? 
                                                            (y - p.y) / (x - p.x) :
                                                            std::numeric_limits<double>::infinity(); }
    };

    struct edge
    {
    public:
        point a;
        point b;

        edge() = default;
        edge(point a, point b) : a(a), b(b) {}
        bool operator==(const edge& p) const { return (a.id == p.a.id && b.id == p.b.id) ||
                                                    (a.id == p.b.id && b.id == p.a.id); }
        // Only for std::set use
        bool operator<(const edge& p) const 
        {
            int min1 = std::min(a.id, b.id),     
                max1 = std::max(a.id, b.id);
            int min2 = std::min(p.a.id, p.b.id), 
                max2 = std::max(p.a.id, p.b.id);
            return std::tie(min1, max1) < std::tie(min2, max2);
        }
    };

    struct circle
    {
    public:
        point center;
        double radius;

        circle() = default; 
        circle(point center, double radius) : center(center), radius(radius) {}
        bool contains(const point& p) const{ return center.distance(p) <= radius; }
        
    };

    struct triangle
    {
    public:
        point a, b, c;

        triangle() = default;
        triangle(point a, point b, point c) : a(a), b(b), c(c) {}
        triangle(const point& a, const edge& e) : a(a), b(e.a), c(e.b) 
        {
            if (a == b || a == c || b == c) 
                throw std::invalid_argument("Invalid triangle");
        }
            
        bool containsVertex(const point& p) const { return a == p || b == p || c == p; }

        double surface() const { return std::abs((a.x * (b.y - c.y) + 
                                                b.x * (c.y - a.y) + 
                                                c.x * (a.y - b.y)) / 2.0); }

        circle circum_circle() const
        {
            double a1 = b.x - a.x, 
                b1 = b.y - a.y, 
                c1 = (a1 * a1 + b1 * b1) / 2;
            double a2 = c.x - a.x, 
                b2 = c.y - a.y, 
                c2 = (a2 * a2 + b2 * b2) / 2;

            double d  = a1 * b2 - a2 * b1;

            point center;
            center.x = a.x + (c1 * b2 - c2 * b1) / d;
            center.y = a.y + (a1 * c2 - a2 * c1) / d;

            return circle(center, center.distance(a));
        }
    };
}