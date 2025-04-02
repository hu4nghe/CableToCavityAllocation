#include "cable_allocator.h"

#include <vector>

int main()
{
    std::vector<cavity> cavities = 
    {
        cavity(49, 16, 710.0,151.0, true ),
        cavity(48, 16, 644.0,151.0, true ),
        cavity(47, 16, 578.0,151.0, true ),
        cavity(46, 16, 512.0,151.0, true ),
        cavity(45, 16, 446.0,151.0, true ),
        cavity(44, 16, 381.0,151.0, true ),
        cavity(43, 16, 315.0,151.0, true ),
        cavity(42, 16, 249.0,151.0, true ),
        cavity(41, 16, 183.0,151.0, true ),
        cavity(40, 16, 118.0,151.0, true ),
        cavity(39, 11, 728.0,99.0, true ),
        cavity(38, 11, 695.0,99.0, true ),
        cavity(37, 11, 662.0,99.0, true ),
        cavity(36, 11, 629.0,99.0, true ),
        cavity(35, 11, 596.0,99.0, true ),
        cavity(34, 11, 563.0,99.0, true ),
        cavity(33, 11, 530.0,99.0, true ),
        cavity(32, 11, 497.0,99.0, true ),
        cavity(31, 11, 464.0,99.0, true ),
        cavity(30, 11, 431.0,99.0, true ),
        cavity(29, 11, 398.0,99.0, true ),
        cavity(28, 11, 365.0,99.0, true ),
        cavity(27, 11, 332.0,99.0, true ),
        cavity(26, 11, 299.0,99.0, true ),
        cavity(25, 11, 266.0,99.0, true ),
        cavity(24, 11, 233.0,99.0, true ),
        cavity(23, 11, 200.0,99.0, true ),
        cavity(22, 11, 167.0,99.0, true ),
        cavity(21, 11, 134.0,99.0, true ),
        cavity(20, 11, 101.0,99.0, true ),
        cavity(19, 11, 711.0,71.0, true ),
        cavity(18, 11, 678.0,71.0, true ),
        cavity(17, 11, 645.0,71.0, true ),
        cavity(16, 11, 612.0,71.0, true ),
        cavity(15, 11, 579.0,71.0, true ),
        cavity(14, 11, 546.0,71.0, true ),
        cavity(13, 11, 513.0,71.0, true ),
        cavity(12, 11, 480.0,71.0, true ),
        cavity(11, 11, 447.0,71.0, true ),
        cavity(10, 11, 414.0,71.0, true ),
        cavity(9, 11, 381.0,71.0, true ),
        cavity(8, 11, 348.0,71.0, true ),
        cavity(7, 11, 315.0,71.0, true ),
        cavity(6, 11, 282.0,71.0, true ),
        cavity(5, 11, 249.0,71.0, true ),
        cavity(4, 11, 216.0,71.0, true ),
        cavity(3, 11, 183.0,71.0, true ),
        cavity(2, 11, 151.0,71.0, true ),
        cavity(1, 11, 118.0,71.0, true )
    };

    cable_allocator allocator(cavities);

    allocator.print_list();
    return  0;
}