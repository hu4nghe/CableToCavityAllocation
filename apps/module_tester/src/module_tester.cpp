#include "connector.h"

#include <vector>
#include <print>
#include <utility>
#include <iostream>

int main()
{
    std::vector<std::tuple<int, int, double, double>> cavities;
    cavities.emplace_back(37, 16, 111, 59);
cavities.emplace_back(36, 16, 177, 59);
cavities.emplace_back(35, 16, 243, 59);
cavities.emplace_back(34, 16, 308, 59);
cavities.emplace_back(33, 16, 374, 59);
cavities.emplace_back(32, 16, 440, 59);
cavities.emplace_back(31, 16, 506, 59);
cavities.emplace_back(30, 16, 572, 59);
cavities.emplace_back(29, 16, 637, 59);
cavities.emplace_back(28, 16, 703, 59);
cavities.emplace_back(27, 16, 80, 121);
cavities.emplace_back(26, 20, 149, 115);
cavities.emplace_back(25, 20, 196, 115);
cavities.emplace_back(24, 20, 243, 115);
cavities.emplace_back(23, 20, 290, 115);
cavities.emplace_back(22, 20, 337, 115);
cavities.emplace_back(21, 20, 384, 115);
cavities.emplace_back(20, 20, 431, 115);
cavities.emplace_back(19, 20, 477, 115);
cavities.emplace_back(18, 20, 524, 115);
cavities.emplace_back(17, 20, 571, 115);
cavities.emplace_back(16, 20, 618, 115);
cavities.emplace_back(15, 20, 665, 115);
cavities.emplace_back(14, 16, 741, 121);
cavities.emplace_back(13, 20, 132, 161);
cavities.emplace_back(12, 20, 178, 161);
cavities.emplace_back(11, 20, 224, 161);
cavities.emplace_back(10, 20, 270, 161);
cavities.emplace_back(9, 20, 315, 161);
cavities.emplace_back(8, 20, 361, 161);
cavities.emplace_back(7, 20, 407, 161);
cavities.emplace_back(6, 20, 453, 161);
cavities.emplace_back(5, 20, 499, 161);
cavities.emplace_back(4, 20, 545, 161);
cavities.emplace_back(3, 20, 591, 161);
cavities.emplace_back(2, 20, 636, 161);
cavities.emplace_back(1, 20, 682, 161);
    
    connector connector_1(cavities);
    connector_1.print_adjacency_list();
    return  0;
}