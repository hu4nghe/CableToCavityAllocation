#pragma once
/**
 * 28/03/2025
 * HHG10 
 * Un algorithme pour trouver tous les solotion possibles d'allocation des cables aux cavités 
 */
#include "cable_region.h"
#include "electronic_container.h"
#include "electronic_component.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>

class cable_allocator
{
private :
    std::vector<cavity> _cavity;

    std::unordered_map<int, std::unordered_set<int>>              _adjacency_list;
    std::unordered_map<int, std::unordered_map<int,cable_region>> _region_table;

public :
    explicit cable_allocator(const std::vector<cavity>&&,const std::vector<cable>&&);
    void     build_region_table();

    //debug functions
    void     print_list() const;
};