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

void console_interaction()
{
    /**
     * prepare python scripts
     */
    auto repository_dir = fs::current_path().parent_path();
    auto python_src_dir = repository_dir / "Python" / "src";

    py::module_ visualizer = py::module_::import("visualizer");
    py::module_ sys        = py::module_::import("sys");
    sys.attr("path").attr("append")(python_src_dir.string());
    
    int cable_idx = 1;
    int idx = 0;
    int mode = 0;

    std::string image_path;

    while (true) 
    {
        std::print("Please enter the image file path: \n");
        std::getline(std::cin, image_path);

        fs::path img_path_fs(image_path);

        if (!fs::exists(img_path_fs)) 
        {
	    std::print("The path does not exist. Try again.\n");
            continue;
        }

       break;
    }

    py::object py_result = visualizer.attr("scan_pins")(image_path);

    std::vector<std::tuple<int, int, double, double>> result;

    for (const auto& item_raw : py_result) 
    {
        py::tuple item = item_raw.cast<py::tuple>(); 
        int index = item[0].cast<int>();
        int gauge = item[1].cast<int>();
        double x   = item[2].cast<double>();
        double y = item[3].cast<double>();
        result.emplace_back(index, gauge, x, y);
    }

    cable_allocator allocator(result);

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
        
        if (allocator.add_cable(wires, mode))
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
    console_interaction();
    return  0;
}

