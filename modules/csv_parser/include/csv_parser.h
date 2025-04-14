#include "cavity.h"
#include "cable.h"

#include <vector>
#include <tuple>

class csv_parser
{
public:
    std::tuple<int, int, double, double> parse_line(std::string_view line) const;
    std::vector<cavity> input_parser(const std::string& filename);
    std::vector<cable> parse_cable(const std::string &filename);

};

