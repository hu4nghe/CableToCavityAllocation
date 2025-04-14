/**
 * @file cable_allocator.h
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Allocator who manages cable connections.
 * @version 1.1
 * @date 2025-04-10
 * 
 * @copyright 
 * Dassault Systemes 2025
 */
#pragma once

#include "cable_region.h"
#include "electronic_container.h"
#include "electronic_component.h"

/**
 * @class cable_allocator
 * @brief Manages the allocation of cables and their connections.
 */
class cable_allocator
{
private:

    std::vector<std::vector<cable_region>>     _solutions;   
    std::map<cable, std::vector<cable_region>> _region_pool;
    connector                                  _connector;

public:

    /**
     * @brief Deleted default constructor to prevent uninitialized allocators.
     */
    cable_allocator() = delete;

    /**
     * @brief Constructs a cable_allocator with a list of cavities.
     * 
     * @param cavities A vector of cavities to initialize the allocator.
     */
    cable_allocator(std::vector<cavity>&& cavities);

    /**
     * @brief Handles console-based interactions for the cable allocator.
     */
    void console_interaction();

    void generate_solution();
private:

    std::tuple<int, int, double, double> parse_line(std::string_view line) const;

    void input_parser(const std::string& filename);

    /**
     * @brief Establishes connections based on the provided mapping.
     * 
     * @param connections A map where keys and values represent connection points.
     */
    void connect(std::map<int, int> connections);
    void disconnect(std::map<int, int> connections);

    /**
     * @brief Adds a new cable to the region pool.
     * 
     * @param new_cable The cable to be added.
     * @return true if the cable was successfully added, false otherwise.
     */
    bool add_cable(cable new_cable);

    /**
     * @brief  Finalizes the allocation of a cable.
     * 
     * @param new_cable The cable to be allocated.
     * @return true if the allocation was successful, false otherwise.
     * @return false if no valid allocation was found.
     */
    bool finalize_allocation(const cable &new_cable);

    /**
     * @brief Handles user input within a specified range.
     * 
     * @param lower The lower bound of the input range.
     * @param upper The upper bound of the input range.
     * @param msg The message to display to the user.
     * @return The validated user input.
     */
    int input(int lower, int upper, const std::string& msg) const;

    /**
     * @brief Gets the size of the region pool.
     * 
     * @return The number of entries in the region pool.
     */
    size_t size() const;

public://debug

    /**
     * @brief Prints the adjacency list for debugging purposes.
     * 
     * This method is intended for debug use only and prints the calculation result.
     */
    void print_adjacency_list() const;
};