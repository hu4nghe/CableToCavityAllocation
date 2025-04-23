#include "connector.h"

#include <vector>
#include <print>
#include <utility>
#include <iostream>

int main()
{
    std::vector<std::tuple<int, int, double, double>> cavities;
    cavities.emplace_back(37, 14, 682.0,161.0);
cavities.emplace_back(36, 14, 636.0,161.0);
cavities.emplace_back(35, 14, 591.0,161.0);
cavities.emplace_back(34, 14, 545.0,161.0);
cavities.emplace_back(33, 14, 499.0,161.0);
cavities.emplace_back(32, 14, 453.0,161.0);
cavities.emplace_back(31, 14, 407.0,161.0);
cavities.emplace_back(30, 14, 361.0,161.0);
cavities.emplace_back(29, 14, 315.0,161.0);
cavities.emplace_back(28, 14, 270.0,161.0);
cavities.emplace_back(27, 14, 224.0,161.0);
cavities.emplace_back(26, 14, 178.0,161.0);
cavities.emplace_back(25, 14, 132.0,161.0);
cavities.emplace_back(24, 14, 665.0,115.0);
cavities.emplace_back(23, 14, 618.0,115.0);
cavities.emplace_back(22, 14, 571.0,115.0);
cavities.emplace_back(21, 14, 524.0,115.0);
cavities.emplace_back(20, 14, 477.0,115.0);
cavities.emplace_back(19, 14, 431.0,115.0);
cavities.emplace_back(18, 14, 384.0,115.0);
cavities.emplace_back(17, 14, 337.0,115.0);
cavities.emplace_back(16, 14, 290.0,115.0);
cavities.emplace_back(15, 14, 243.0,115.0);
cavities.emplace_back(14, 14, 196.0,115.0);
cavities.emplace_back(13, 14, 149.0,115.0);
cavities.emplace_back(12, 23, 741.0,121.0);
cavities.emplace_back(11, 23, 80.0,121.0);
cavities.emplace_back(10, 23, 703.0,59.0);
cavities.emplace_back(9, 23, 637.0,59.0);
cavities.emplace_back(8, 22, 572.0,59.0);
cavities.emplace_back(7, 23, 506.0,59.0);
cavities.emplace_back(6, 23, 440.0,59.0);
cavities.emplace_back(5, 23, 374.0,59.0);
cavities.emplace_back(4, 23, 308.0,59.0);
cavities.emplace_back(3, 23, 243.0,59.0);
cavities.emplace_back(2, 23, 177.0,59.0);
cavities.emplace_back(1, 23, 111.0,59.0);
    
    connector connector_1(cavities);
    connector_1.print_adjacency_list();
    return  0;
}