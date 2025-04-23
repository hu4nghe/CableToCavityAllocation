#include "connector.h"

#include <vector>
#include <print>
#include <utility>
#include <iostream>

int main()
{
    std::vector<std::tuple<int, int, double, double>> cavities;
    cavities.emplace_back(1, 16, 111.0,59.0);
    cavities.emplace_back(2, 16, 177.0,59.0);
    cavities.emplace_back(3, 16, 243.0,59.0);
    cavities.emplace_back(4, 16, 308.0,59.0);
    cavities.emplace_back(5, 16, 374.0,59.0);
    cavities.emplace_back(6, 16, 440.0,59.0);
    cavities.emplace_back(7, 16, 506.0,59.0);
    cavities.emplace_back(8, 16, 572.0,59.0);
    cavities.emplace_back(9, 16, 637.0,59.0);
    cavities.emplace_back(10, 16, 703.0,59.0);
    cavities.emplace_back(11, 16, 80.0,121.0);
    cavities.emplace_back(12, 20, 149.0,115.0);
    cavities.emplace_back(13, 20, 196.0,115.0);
    cavities.emplace_back(14, 20, 243.0,115.0);
    cavities.emplace_back(15, 20, 290.0,115.0);
    cavities.emplace_back(16, 20, 337.0,115.0);
    cavities.emplace_back(17, 20, 384.0,115.0);
    cavities.emplace_back(18, 20, 431.0,115.0);
    cavities.emplace_back(19, 20, 477.0,115.0);
    cavities.emplace_back(20, 20, 524.0,115.0);
    cavities.emplace_back(21, 20, 571.0,115.0);
    cavities.emplace_back(22, 20, 618.0,115.0);
    cavities.emplace_back(23, 20, 665.0,115.0);
    cavities.emplace_back(24, 16, 741.0,121.0);
    cavities.emplace_back(25, 20, 132.0,161.0);
    cavities.emplace_back(26, 20, 178.0,161.0);
    cavities.emplace_back(27, 20, 224.0,161.0);
    cavities.emplace_back(28, 20, 270.0,161.0);
    cavities.emplace_back(29, 20, 315.0,161.0);
    cavities.emplace_back(30, 20, 361.0,161.0);
    cavities.emplace_back(31, 20, 407.0,161.0);
    cavities.emplace_back(32, 20, 453.0,161.0);
    cavities.emplace_back(33, 20, 499.0,161.0);
    cavities.emplace_back(34, 20, 545.0,161.0);
    cavities.emplace_back(35, 20, 591.0,161.0);
    cavities.emplace_back(36, 20, 636.0,161.0);
    cavities.emplace_back(37, 20, 682.0,161.0);
    
    connector connector_1(cavities);
    connector_1.print_adjacency_list();
    return  0;
}