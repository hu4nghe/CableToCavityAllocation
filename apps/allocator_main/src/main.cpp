#include "cable_allocator.h"

#include <print>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ranges>

#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;
namespace fs = std::filesystem;

fs::path read_file(const std::string& target_ext,
                   const std::string& hint)
{
    fs::path input_path_fs;
    while (true) 
    {
        std::string input_path;
        std::print("{}",hint);
        std::getline(std::cin, input_path);
        input_path_fs = input_path;
        if (!fs::exists(input_path_fs)) 
	        std::print("The path does not exist, try again.\n");
        else if (input_path_fs.extension() != target_ext)
            std::print("The format is not supported, try again.\n");
        else break;
    }
    return input_path_fs;
}

void console_interaction()
{
    // prepare python scripts
    auto repository_dir = fs::current_path().parent_path();
    auto python_src_dir = fs::absolute(repository_dir / "Python" / "src");
    py::module_ sys        = py::module_::import("sys");
    sys.attr("path").attr("append")(python_src_dir.string());
    py::module_ visualizer = py::module_::import("visualizer");
    
    int cable_idx = 1;
    int mode = 0;

    // Build connector object from a connector image.
    const std::string& connector_hint = "Please enter the image file path: \n";
    const std::string& connector_ext  = ".png";
    py::object py_result = 
        visualizer.attr("scan_pins")
                       (read_file(connector_ext, connector_hint).string());

    // Parse python tuple                   
    std::vector<std::tuple<int, int, double, double>> result;
    for (const auto& item_raw : py_result) 
    {
        py::tuple item = item_raw.cast<py::tuple>(); 
        int index = item[0].cast<int>();
        int gauge = item[1].cast<int>();
        double x  = item[2].cast<double>();
        double y  = item[3].cast<double>();
        result.emplace_back(index, gauge, x, y);
    }

    cable_allocator allocator(result);

    // Read cable data
    auto input_file_path = fs::absolute(repository_dir / "data" / "cable_data.csv");
    std::ifstream cable_input_file(input_file_path.string());
    std::string line;

    // Ignore first line
    std::getline(cable_input_file, line);

    // Parse cable data
    std::map<int, std::vector<std::tuple<int, int>>> cable_data;
    while (std::getline(cable_input_file, line)) 
    {
        std::istringstream iss(line);

        std::string token;
        int cable_idx = 0;
        int gauge     = 0;
        int num_wires = 0;

        if (std::getline(iss, token, ',')) 
            cable_idx = std::stoi(token);
        if (std::getline(iss, token, ',')) 
            gauge = std::stoi(token);
        if (std::getline(iss, token, ',')) 
            num_wires = std::stoi(token);

        cable_data[cable_idx].emplace_back(gauge, num_wires);
    }

    // Generate and print allocations
    for (auto& [cable_idx, wires] : cable_data) 
    {
        if (allocator.add_cable(wires, mode)) 
        {
            auto allocations = allocator.get_cable_allocations(cable_idx);
            for (const auto& [i, allocation_tuple] : std::views::enumerate(allocations)) 
            {
                const auto& [score, allocation] = allocation_tuple;
                std::print("Cable {} - Allocation {}, Score: {}\n", cable_idx, i, score);
                for (const auto& cavity_ID : allocation)
                    std::print("cavity {}\n", cavity_ID);
            }

            int allocation_idx;
            std::print("Choose allocation index for cable {}: ", cable_idx);
            std::cin >> allocation_idx;

            allocator.confirme_allocation(cable_idx, allocation_idx);

            auto status = allocator.get_connector_status();
            visualizer.attr("visualize_connector")(status);

            mode = cable_idx == 0 ? 0 : 1;
        } 
        else 
            std::print("Invalid cable input for cable {}.\n", cable_idx);
    }
}

int main()
{
    py::scoped_interpreter guard{}; 
    console_interaction();
    return  0;
}
