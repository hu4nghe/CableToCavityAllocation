/**
 * @file geometry_tool_base.h
 * @author 
 * HUANG He (he.huang@utt.fr)
 * @brief
 * This file defines serveral basical structure for geometry calculations
 * @version 2.0
 * @date 2025-07-09
 *
 */

#pragma once
 
#include <cmath>
#include <stdexcept>

namespace geo_tools
{
    static auto get_dbl_delta =
        [](double a, 
           double b, 
           double epsilon = std::numeric_limits<double>::epsilon())
        { 
            auto diff  = a - b;
            auto abs_a = std::fabs(a);
            auto abs_b = std::fabs(b);
            auto max_val = std::max(abs_a, abs_b);
            return std::tuple(diff, max_val * epsilon);
        };
    static auto dbl_eq = 
        [](double a, 
           double b, 
           double epsilon = std::numeric_limits<double>::epsilon())
        { 
            auto [diff, relative_epsilon] = get_dbl_delta(a, b, epsilon);
            return std::fabs(diff) <= relative_epsilon;
        };
    static auto dbl_inf = 
        [](double a, 
           double b, 
           double epsilon = std::numeric_limits<double>::epsilon())
        { 
            auto [diff, relative_epsilon] = get_dbl_delta(a, b, epsilon);
            return -diff > relative_epsilon;
        };



    struct point
    {
    public:
        int id;
        double x, y;

        point() = default;
        point(int id, double x, double y) : 
            id(id), 
            x(x), 
            y(y) {}

        bool operator==(const point& p) const 
        { 
            return id == p.id && dbl_eq(x, p.x) && dbl_eq(y, p.y); 
        }
        bool operator!=(const point& p) const 
        { 
            return !(*this == p); 
        }
        bool operator< (const point& p) const 
        { 
            return dbl_eq(x, p.x) ? dbl_inf(y, p.y) : dbl_inf(x, p.x); 
        }
        bool operator> (const point& p) const 
        { 
            return (*this != p) && !(*this < p); 
        }
        double distance(const point& p) const 
        { 
            return std::sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)); 
        }
        double slope   (const point& p) const 
        { 
            return dbl_eq(x, p.x) ? std::numeric_limits<double>::infinity() : (y - p.y) / (x - p.x);
        }
        
    };

    struct edge
    {
    public:
        point a;
        point b;

        edge() = default;
        edge(point a, point b) : 
            a(a > b ? a : b), 
            b(a > b ? b : a) {}

        bool operator==(const edge& p) const 
        { 
            return a == p.a && b == p.b; 
        }

        bool operator< (const edge& p) const 
        { 
            return a == p.a ? b < p.b : a < p.a; 
        }
    };

    struct circle
    {
    public:
        point center;
        double radius;

        circle() = default; 
        circle(point center, double radius) : 
            center(center), 
            radius(radius) {}
        bool contains(const point& p) const
        { 
            return center.distance(p) <= radius; 
        }
        
    };

    struct triangle
    {
    public:
        point a, b, c;

        triangle() = default;
        triangle(point a, point b, point c) : 
            a(a), 
            b(b), 
            c(c) 
        {
            if (a == b || a == c || b == c) 
                throw std::invalid_argument("Invalid triangle");
        }
        triangle(const point& a, const edge& e) : 
            a(a), 
            b(e.a), 
            c(e.b) 
        {
            if (a == b || a == c || b == c) 
                throw std::invalid_argument("Invalid triangle");
        }
            
        bool containsVertex(const point& p) const 
        { 
            return a == p || b == p || c == p; 
        }

        circle circum_circle() const
        {
            double  a1 = b.x - a.x, 
                    b1 = b.y - a.y, 
                    c1 = (a1 * a1 + b1 * b1) / 2,
                    a2 = c.x - a.x, 
                    b2 = c.y - a.y, 
                    c2 = (a2 * a2 + b2 * b2) / 2,
                    d  = a1 * b2 - a2 * b1;

            point center;
            center.x = a.x + (c1 * b2 - c2 * b1) / d;
            center.y = a.y + (a1 * c2 - a2 * c1) / d;

            return circle(center, center.distance(a));
        }
    };
}