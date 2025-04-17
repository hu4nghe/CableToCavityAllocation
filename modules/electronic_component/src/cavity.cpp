/**
 * @file cavity.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cavity class's 2D calculation
 * @version 1.2
 * @date 2025-04-17
 * 
 * @copyright 
 * Dassault Systemes 2025
 * 
 */
#include "cavity.h"

#include <cmath>

double cavity::distance(const std::pair<double, double>& point) const
{
   return sqrt(pow(point.first  - _position.first ,2) + 
               pow(point.second - _position.second,2));
}

std::pair<double, double> cavity::midpoint(const cavity &other) const
{
    return std::make_pair<double, double>((_position.first  + other._position.first ) / 2.0,
                                          (_position.second + other._position.second) / 2.0);
}
