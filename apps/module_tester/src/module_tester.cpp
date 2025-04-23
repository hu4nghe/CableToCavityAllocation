#include "connector.h"

#include <vector>
#include <print>
#include <utility>
#include <iostream>

int main()
{
    std::vector<std::tuple<int, int, double, double>> cavities;
    cavities.emplace_back(78, 9, 610, 147);
    cavities.emplace_back(77, 9, 577, 147);
    cavities.emplace_back(76, 9, 544, 147);
    cavities.emplace_back(75, 9, 511, 147);
    cavities.emplace_back(74, 9, 478, 147);
    cavities.emplace_back(73, 9, 412, 147);
    cavities.emplace_back(72, 9, 379, 147);
    cavities.emplace_back(71, 9, 346, 147);
    cavities.emplace_back(70, 9, 313, 147);
    cavities.emplace_back(69, 9, 280, 147);
    cavities.emplace_back(68, 9, 247, 147);
    cavities.emplace_back(67, 9, 214, 147);
    cavities.emplace_back(66, 9, 181, 147);
    cavities.emplace_back(65, 9, 148, 147);
    cavities.emplace_back(64, 9, 115, 147);
    cavities.emplace_back(63, 9, 709, 146);
    cavities.emplace_back(62, 9, 676, 146);
    cavities.emplace_back(61, 9, 643, 146);
    cavities.emplace_back(60, 9, 445, 146);
    cavities.emplace_back(59, 9, 726, 119);
    cavities.emplace_back(58, 9, 693, 119);
    cavities.emplace_back(57, 9, 660, 119);
    cavities.emplace_back(56, 9, 627, 119);
    cavities.emplace_back(55, 9, 594, 119);
    cavities.emplace_back(54, 9, 561, 119);
    cavities.emplace_back(53, 9, 528, 119);
    cavities.emplace_back(52, 9, 495, 119);
    cavities.emplace_back(51, 9, 462, 119);
    cavities.emplace_back(50, 9, 429, 119);
    cavities.emplace_back(49, 9, 396, 119);
    cavities.emplace_back(48, 9, 363, 119);
    cavities.emplace_back(47, 9, 330, 119);
    cavities.emplace_back(46, 9, 297, 119);
    cavities.emplace_back(45, 9, 264, 119);
    cavities.emplace_back(44, 9, 231, 119);
    cavities.emplace_back(43, 9, 198, 119);
    cavities.emplace_back(42, 9, 165, 119);
    cavities.emplace_back(41, 9, 132, 119);
    cavities.emplace_back(40, 9, 99, 119);
    cavities.emplace_back(39, 9, 379, 91);
    cavities.emplace_back(38, 9, 346, 91);
    cavities.emplace_back(37, 9, 313, 91);
    cavities.emplace_back(36, 9, 280, 91);
    cavities.emplace_back(35, 9, 247, 91);
    cavities.emplace_back(34, 9, 214, 91);
    cavities.emplace_back(33, 9, 181, 91);
    cavities.emplace_back(32, 9, 148, 91);
    cavities.emplace_back(31, 9, 115, 91);
    cavities.emplace_back(30, 9, 709, 91);
    cavities.emplace_back(29, 9, 676, 91);
    cavities.emplace_back(28, 9, 643, 91);
    cavities.emplace_back(27, 9, 610, 91);
    cavities.emplace_back(26, 9, 577, 91);
    cavities.emplace_back(25, 9, 544, 91);
    cavities.emplace_back(24, 9, 511, 91);
    cavities.emplace_back(23, 9, 478, 91);
    cavities.emplace_back(22, 9, 445, 91);
    cavities.emplace_back(21, 9, 412, 91);
    cavities.emplace_back(20, 9, 726, 63);
    cavities.emplace_back(19, 9, 693, 63);
    cavities.emplace_back(18, 9, 660, 63);
    cavities.emplace_back(17, 9, 627, 63);
    cavities.emplace_back(16, 9, 594, 63);
    cavities.emplace_back(15, 9, 561, 63);
    cavities.emplace_back(14, 9, 528, 63);
    cavities.emplace_back(13, 9, 495, 63);
    cavities.emplace_back(12, 9, 462, 63);
    cavities.emplace_back(11, 9, 429, 63);
    cavities.emplace_back(10, 9, 396, 63);
    cavities.emplace_back(9, 9, 363, 63);
    cavities.emplace_back(8, 9, 330, 63);
    cavities.emplace_back(7, 9, 297, 63);
    cavities.emplace_back(6, 9, 264, 63);
    cavities.emplace_back(5, 9, 231, 63);
    cavities.emplace_back(4, 9, 198, 63);
    cavities.emplace_back(3, 9, 132, 63);
    cavities.emplace_back(2, 9, 99, 63);
    cavities.emplace_back(1, 9, 165, 63);
    
    connector connector_1(cavities);
    connector_1.print_adjacency_list();
    return  0;
}