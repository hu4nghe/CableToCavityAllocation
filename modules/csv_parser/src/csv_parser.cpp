#include "csv_parser.h"

#include <fstream>

std::tuple<int, int, double, double> csv_parser::parse_line(std::string_view line) const
{
    std::tuple<int, int, double, double> result;
    auto pos = 0;
    auto parse = [&](auto& value) 
    {
        auto next = line.find(',', pos);
        std::from_chars(line.data() + pos, line.data() + next, value);
        pos = next + 1;
    };
    
    parse(std::get<0>(result));
    parse(std::get<1>(result));
    parse(std::get<2>(result));
    parse(std::get<3>(result));

    return result;
}

std::vector<cavity> csv_parser::input_parser(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<cavity> data;
    
    while (std::getline(file, line)) 
        data.emplace_back(std::make_from_tuple<cavity>(parse_line(line)));

    return std::move(data);
}