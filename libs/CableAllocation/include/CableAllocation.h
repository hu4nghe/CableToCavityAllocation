#pragma once

#include "Cavity.h"
#include "Cable.h"

#include <vector>
#include <map>
#include <unordered_set>

class cable_allocator
{
    private :
        std::map<int, std::unordered_set<int>> _adjacency_list;

    public :
    cable_allocator() = default;

    void build_adjacency_list(const std::vector<Cavity>);
    void print_list() const;
};