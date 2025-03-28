#pragma once

#include "Cavity.h"
#include "Cable.h"

#include <vector>
#include <unordered_map>

class cable_allocator
{
    private :
        std::unordered_map<int, std::vector<int>> _adjacency_list;

    public :
    cable_allocator() = default;

    void build_adjacency_list(const std::vector<Cavity>);
    void print_list() const;
};