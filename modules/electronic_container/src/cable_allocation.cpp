/**
 * @file cable_allocation.cpp
 * @author 
 * HUANG He (he.huang.intern@3ds.com)
 * @brief 
 * Implementation of the cable_allocation class.
 * @version 2.0
 * @date 2025-07-09
 * 
 * @copyright 
 * Dassault Systemes 2025
 *
 */

#include "cable_allocation.h"
#include "min_enclosing_circle.h"

#include <cmath>
#include <stdexcept>
#include <queue>
#include <unordered_set>

cable_allocation::cable_allocation(const std::vector<int>&          connections,
                                         std::shared_ptr<connector> sp_connector) :
    _reserved_cavities(connections.begin(), connections.end()),
    _score {}
{
    if (!sp_connector) throw std::runtime_error("connector is not valid.");

    // --- 1. Compactness: minimum enclosing circle radius of this allocation's cavities ---
    std::vector<std::pair<double,double>> coords;
    for (const auto& cavity_id : connections)
        coords.push_back(sp_connector->get_component(cavity_id)->get_pos());
    const double mec_radius = std::ceil(geo_tools::calculate_min_enclosing_circle_radius(coords));

    // --- 2. Adjacency: Delaunay edges from this allocation's cavities to
    //        cavities already occupied by previously placed cables.
    //        Intra-allocation edges are excluded to avoid self-counting.
    //        This metric is zero for the first cable (no prior placements). ---
    int adjacency_count = 0;
    for (const auto& cavity_id : _reserved_cavities)
        for (const auto& neighbor_id : sp_connector->get_adj_list(cavity_id))
            if (!_reserved_cavities.count(neighbor_id))
            {
                auto neighbor = sp_connector->get_component(neighbor_id);
                if (neighbor && neighbor->status() != 0)
                    ++adjacency_count;
            }

    // --- 3. Fragment count: connected components among remaining available
    //        cavities after this allocation is tentatively placed.
    //        A result of 1 means the free space stays fully connected.
    //        Values > 1 indicate isolated pockets that mode=1 cables can never
    //        reach, so we penalise them in the ordering.
    //        BFS runs on the Delaunay adjacency graph restricted to free cavities. ---
    std::unordered_set<int> remaining;
    for (const auto& cav : *sp_connector)
        if (cav->status() == 0 && !_reserved_cavities.count(cav->get_ID()))
            remaining.insert(cav->get_ID());

    int fragment_count = 0;
    std::unordered_set<int> visited;
    for (const int start_id : remaining)
    {
        if (visited.count(start_id)) continue;
        ++fragment_count;
        std::queue<int> bfs;
        bfs.push(start_id);
        visited.insert(start_id);
        while (!bfs.empty())
        {
            const int cur = bfs.front(); bfs.pop();
            for (const int nb : sp_connector->get_adj_list(cur))
                if (remaining.count(nb) && !visited.count(nb))
                {
                    visited.insert(nb);
                    bfs.push(nb);
                }
        }
    }

    _score = AllocationScore{ mec_radius, adjacency_count, fragment_count };
}

bool cable_allocation::operator<(const cable_allocation &other) const noexcept
{
    if (_reserved_cavities == other._reserved_cavities) 
        return false;
    
    if (_score == other._score) 
        return _reserved_cavities < other._reserved_cavities; 
    
    return _score < other._score; 
}