#pragma once
/**
 * 28/03/2025
 * HHG10 
 * Un algorithme pour trouver tous les solotion possibles d'allocation des cables aux cavités 
 */
#include "Cavity.h"
#include "Cable.h"

#include <vector>
#include <map>
#include <unordered_set>

class cable_region
{
private :
    std::vector<int>                _cavities;
    std::vector<std::pair<int,int>> _segments;
public:

};

class cable_allocator
{
private :
    std::vector<Cavity> _cavity;

    std::unordered_map<int, std::unordered_set<int>>          _adjacency_list;
    std::unordered_map<int, std::unordered_set<cable_region>> _region_table;

public :
    explicit cable_allocator(const std::vector<Cavity>&&);
    void     build_region_table();

    //debug functions
    void     print_list() const;
};