#include "cable_allocator.h"

#include <print>
#include <ranges>
#include <iostream>
#include <sstream>
#include <filesystem>

#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;
namespace fs = std::filesystem;

void console_interaction(cable_allocator& allocator)
{
    auto repo_dir = fs::current_path().parent_path();
    auto python_src_dir = fs::absolute(repo_dir / "Python" / "src");
    py::module_ sys = py::module_::import("sys");
    sys.attr("path").attr("append")(python_src_dir.string());

    py::module_ visualizer = py::module_::import("visualizer");

    int cable_idx = 1;
    int idx = 0;
    int mode = 0;
    while (true)
    {
        std::vector<std::tuple<int,int>> wires;
        std::string input_line;

        std::print("Enter groups of data (gauge number_of_wires), or type 'end' to finish:\n");
        
        while (true)
        {
            std::getline(std::cin, input_line);
            
            // Skip empty lines
            if (input_line.empty())
                continue;

            // Check if the user wants to end the input
            if (input_line == "end")
                break;

            // Parse the input line
            std::istringstream iss(input_line);
            int gauge, num_wires;
            if (!(iss >> gauge >> num_wires))
            {
                std::print("Invalid input. Please enter two integers (gauge number_of_wires) or 'end'.\n");
                continue;
            }

            wires.emplace_back(gauge, num_wires);
            
        }
        
        if(allocator.add_cable(wires, mode))
        {
            auto allocations = allocator.get_cable_allocations(cable_idx);
            for (const auto& [i, allocation_tuple] : std::views::enumerate(allocations))
            {
                const auto& [score, allocation] = allocation_tuple;
                std::print("Allocation {}, Score :{}\n", i, score);
                for (const auto& cavity_ID : allocation)
                    std::print("cavity {}\n",  cavity_ID);
            }
            std::cin>>idx;
            allocator.confirme_allocation(cable_idx,idx);

            auto status = allocator.get_connector_status();
            visualizer.attr("visualize_connector")(status); 

            cable_idx++;
            mode = cable_idx == 1 ? 0 : 1;
        }
        else 
        {
            std::print("Void input.\n");
            continue;
        }
    }
}

int main()
{

    py::scoped_interpreter guard{}; 

    std::vector<std::tuple<int, int, double, double>> cavities;
    cavities.emplace_back(49, 16, 710.0,151.0);
    cavities.emplace_back(48, 16, 644.0,151.0);
    cavities.emplace_back(47, 16, 578.0,151.0);
    cavities.emplace_back(46, 16, 512.0,151.0);
    cavities.emplace_back(45, 16, 446.0,151.0);
    cavities.emplace_back(44, 16, 381.0,151.0);
    cavities.emplace_back(43, 16, 315.0,151.0);
    cavities.emplace_back(42, 16, 249.0,151.0);
    cavities.emplace_back(41, 16, 183.0,151.0);
    cavities.emplace_back(40, 16, 118.0,151.0);
    cavities.emplace_back(39, 22, 728.0,99.0);
    cavities.emplace_back(38, 22, 695.0,99.0);
    cavities.emplace_back(37, 22, 662.0,99.0);
    cavities.emplace_back(36, 22, 629.0,99.0);
    cavities.emplace_back(35, 22, 596.0,99.0);
    cavities.emplace_back(34, 22, 563.0,99.0);
    cavities.emplace_back(33, 22, 530.0,99.0);
    cavities.emplace_back(32, 22, 497.0,99.0);
    cavities.emplace_back(31, 22, 464.0,99.0);
    cavities.emplace_back(30, 22, 431.0,99.0);
    cavities.emplace_back(29, 22, 398.0,99.0);
    cavities.emplace_back(28, 22, 365.0,99.0);
    cavities.emplace_back(27, 22, 332.0,99.0);
    cavities.emplace_back(26, 22, 299.0,99.0);
    cavities.emplace_back(25, 22, 266.0,99.0);
    cavities.emplace_back(24, 22, 233.0,99.0);
    cavities.emplace_back(23, 22, 200.0,99.0);
    cavities.emplace_back(22, 22, 167.0,99.0);
    cavities.emplace_back(21, 22, 134.0,99.0);
    cavities.emplace_back(20, 22, 101.0,99.0);
    cavities.emplace_back(19, 22, 711.0,71.0);
    cavities.emplace_back(18, 22, 678.0,71.0);
    cavities.emplace_back(17, 22, 645.0,71.0);
    cavities.emplace_back(16, 22, 612.0,71.0);
    cavities.emplace_back(15, 22, 579.0,71.0);
    cavities.emplace_back(14, 22, 546.0,71.0);
    cavities.emplace_back(13, 22, 513.0,71.0);
    cavities.emplace_back(12, 22, 480.0,71.0);
    cavities.emplace_back(11, 22, 447.0,71.0);
    cavities.emplace_back(10, 22, 414.0,71.0);
    cavities.emplace_back(9, 22, 381.0,71.0);
    cavities.emplace_back(8, 22, 348.0,71.0);
    cavities.emplace_back(7, 22, 315.0,71.0);
    cavities.emplace_back(6, 22, 282.0,71.0);
    cavities.emplace_back(5, 22, 249.0,71.0);
    cavities.emplace_back(4, 22, 216.0,71.0);
    cavities.emplace_back(3, 22, 183.0,71.0);
    cavities.emplace_back(2, 22, 151.0,71.0);
    cavities.emplace_back(1, 22, 118.0,71.0);


    cable_allocator allocator(cavities);
    console_interaction(allocator);
    return  0;
}

