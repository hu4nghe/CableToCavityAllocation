#include "csv_parser.h"

#include <fstream>
#include <sstream>
#include "cable.h"

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
std::vector<cable> csv_parser::parse_cable(const std::string& filename) 
{
    std::vector<cable> cables;
    std::ifstream file(filename);
    
    std::string line;
    while (std::getline(file, line)) 
    {

        // 移除行尾的换行符和空格
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        std::istringstream iss(line);
        std::string token;
        if (!std::getline(iss, token, ',')) {
            continue; // 跳过格式错误的行
        }

        int cable_id = std::stoi(token);

        while (std::getline(iss, token, ',')) 
        {
            std::vector<wire> wires;
            size_t colon_pos = token.find(':');
            if (colon_pos != std::string::npos) 
            {
                auto gauge = std::stoi(token.substr(0, colon_pos));
                auto wire_count = std::stoi(token.substr(colon_pos + 1));
                for(auto i = 0; i < wire_count; ++i) 
                {
                    wires.emplace_back(i, gauge);
                }
                cables.emplace_back(cable_id, std::move(wires));
            }
        }
    }

    return cables;
}