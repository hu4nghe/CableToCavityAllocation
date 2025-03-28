#include "Cavity.h"
#include "CableAllocation.h"
#include <vector>

int main()
{
    cable_allocator allocator;

    std::vector<Cavity> cavities = 
    {
        Cavity(1, 35, 0.593,0.615, true ),
        Cavity(2, 35, 0.397,0.615, true ),
        Cavity(3, 35, 0.2  ,0.615, true ),
        Cavity(4, 35, 0.697,0.405, true ),
        Cavity(5, 35, 0.497,0.405, true ),
        Cavity(6, 35, 0.297,0.405, true ),
        Cavity(7, 35, 0.098,0.405, true ),

    };

    allocator.build_adjacency_list(cavities);
    allocator.print_list();
    return  0;
}