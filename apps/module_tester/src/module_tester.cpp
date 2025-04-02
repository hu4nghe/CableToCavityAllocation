#include "electronic_component.h"
#include "electronic_container.h"

#include <print>

int main()
{
    cavity c1(1,20,5,5,true);
    wire w1(1,20);

    std::print("the result is : {}\n",c1.is_compatible(w1));
    return 0;
}