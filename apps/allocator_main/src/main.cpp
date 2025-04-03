#include "cable_allocator.h"

#include <vector>

int main()
{
    std::vector<cavity> cavities = 
    {
        /*cavity(49, 16, 710.0,151.0, true ),
        cavity(48, 16, 644.0,151.0, true ),
        cavity(47, 16, 578.0,151.0, true ),
        cavity(46, 16, 512.0,151.0, true ),
        cavity(45, 16, 446.0,151.0, true ),
        cavity(44, 16, 381.0,151.0, true ),
        cavity(43, 16, 315.0,151.0, true ),
        cavity(42, 16, 249.0,151.0, true ),
        cavity(41, 16, 183.0,151.0, true ),
        cavity(40, 16, 118.0,151.0, true ),
        cavity(39, 22, 728.0,99.0, true ),
        cavity(38, 22, 695.0,99.0, true ),
        cavity(37, 22, 662.0,99.0, true ),
        cavity(36, 22, 629.0,99.0, true ),
        cavity(35, 22, 596.0,99.0, true ),
        cavity(34, 22, 563.0,99.0, true ),
        cavity(33, 22, 530.0,99.0, true ),
        cavity(32, 22, 497.0,99.0, true ),
        cavity(31, 22, 464.0,99.0, true ),
        cavity(30, 22, 431.0,99.0, true ),
        cavity(29, 22, 398.0,99.0, true ),
        cavity(28, 22, 365.0,99.0, true ),
        cavity(27, 22, 332.0,99.0, true ),
        cavity(26, 22, 299.0,99.0, true ),
        cavity(25, 22, 266.0,99.0, true ),
        cavity(24, 22, 233.0,99.0, true ),*/
        cavity(23, 22, 200.0,99.0, true ),
        cavity(22, 22, 167.0,99.0, true ),
        cavity(21, 22, 134.0,99.0, true ),
        cavity(20, 22, 101.0,99.0, false ),
        /*cavity(19, 22, 711.0,71.0, true ),
        cavity(18, 22, 678.0,71.0, true ),
        cavity(17, 22, 645.0,71.0, true ),
        cavity(16, 22, 612.0,71.0, true ),
        cavity(15, 22, 579.0,71.0, true ),
        cavity(14, 22, 546.0,71.0, true ),
        cavity(13, 22, 513.0,71.0, true ),
        cavity(12, 22, 480.0,71.0, true ),
        cavity(11, 22, 447.0,71.0, true ),
        cavity(10, 22, 414.0,71.0, true ),
        cavity(9, 22, 381.0,71.0, true ),
        cavity(8, 22, 348.0,71.0, true ),
        cavity(7, 22, 315.0,71.0, true ),
        cavity(6, 22, 282.0,71.0, true ),
        cavity(5, 22, 249.0,71.0, true ),
        cavity(4, 22, 216.0,71.0, true ),*/
        cavity(3, 22, 183.0,71.0, true ),
        cavity(2, 22, 151.0,71.0, false ),
        cavity(1, 22, 118.0,71.0, true )
    };
    std::vector<wire> c1 =
    {
        wire(1,22),
        wire(2,22),
    };
    std::vector<wire> c2 = 
    {
        wire(3,22),
        wire(4,22),
        wire(5,22)
    };
    
    cable cab1(1,c1);
    cable cab2(2,c2);

    std::vector<cable> cable_vector{ cab1 };


    cable_allocator allocator(cavities,cable_vector);
    //allocator.print_list();

    allocator.generate_region_table();
    //allocator.print_region_list();
    
    allocator.allocate_cables();
    allocator.print_solutions();
    return  0;
}