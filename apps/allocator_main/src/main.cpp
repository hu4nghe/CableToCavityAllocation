#include "cable_allocator.h"

#include <vector>
#include <print>

int main()
{
    std::vector<cavity> cavities = 
    {
        /*cavity(49, 16, 710.0,151.0),
        cavity(48, 16, 644.0,151.0),
        cavity(47, 16, 578.0,151.0),
        cavity(46, 16, 512.0,151.0),
        cavity(45, 16, 446.0,151.0),
        cavity(44, 16, 381.0,151.0),
        cavity(43, 16, 315.0,151.0),
        cavity(42, 16, 249.0,151.0),
        cavity(41, 16, 183.0,151.0),
        cavity(40, 16, 118.0,151.0),
        cavity(39, 22, 728.0,99.0),
        cavity(38, 22, 695.0,99.0),
        cavity(37, 22, 662.0,99.0),
        cavity(36, 22, 629.0,99.0),
        cavity(35, 22, 596.0,99.0),
        cavity(34, 22, 563.0,99.0),
        cavity(33, 22, 530.0,99.0),
        cavity(32, 22, 497.0,99.0),
        cavity(31, 22, 464.0,99.0),
        cavity(30, 22, 431.0,99.0),
        cavity(29, 22, 398.0,99.0),
        cavity(28, 22, 365.0,99.0),
        cavity(27, 22, 332.0,99.0),
        cavity(26, 22, 299.0,99.0),*/
        cavity(25, 22, 266.0,99.0),
        cavity(24, 22, 233.0,99.0),
        cavity(23, 22, 200.0,99.0),
        cavity(22, 22, 167.0,99.0),
        cavity(21, 22, 134.0,99.0),
        cavity(20, 22, 101.0,99.0),
        /*cavity(19, 22, 711.0,71.0),
        cavity(18, 22, 678.0,71.0),
        cavity(17, 22, 645.0,71.0),
        cavity(16, 22, 612.0,71.0),
        cavity(15, 22, 579.0,71.0),
        cavity(14, 22, 546.0,71.0),
        cavity(13, 22, 513.0,71.0),
        cavity(12, 22, 480.0,71.0),
        cavity(11, 22, 447.0,71.0),
        cavity(10, 22, 414.0,71.0),
        cavity(9, 22, 381.0,71.0),
        cavity(8, 22, 348.0,71.0),
        cavity(7, 22, 315.0,71.0),
        cavity(6, 22, 282.0,71.0),*/
        cavity(5, 22, 249.0,71.0),
        cavity(4, 22, 216.0,71.0),
        cavity(3, 22, 183.0,71.0),
        cavity(2, 22, 151.0,71.0),
        cavity(1, 22, 118.0,71.0)
    };
    std::vector<wire> c1 = //cable with 2 wires
    {
        wire(1,22),
        wire(2,22),
    };
    
    std::vector<wire> c2 = //cable with 3 wires
    {
        wire(3,22),
        wire(4,22),
        wire(5,22)
    };
    
    cable cab1(1,c1);
    cable cab2(2,c2);


    cable_allocator allocator(cavities);
    allocator.add_cable(cab1);
    std::print("cab1 added.\n");
    
    allocator.print_current_solutions();
    allocator.add_cable(cab2);
    

    //allocator.print_adjacency_list();
    //allocator.print_region_list();
    allocator.print_current_solutions();
    return  0;
}