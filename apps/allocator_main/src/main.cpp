#include "cable_allocator.h"
#include "csv_parser.h"

int main()
{
    csv_parser parser;
    cable_allocator allocator(parser.input_parser("cavities.csv"));
    allocator.read_cable_datas();
    allocator.print_solutions();
    return  0;
}