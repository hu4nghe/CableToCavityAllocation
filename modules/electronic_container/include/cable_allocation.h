/**
 * @file cable_allocation.h
 * @author
 * HUANG He (he.huang.intern@3ds.com)
 * @brief
 * A set of possible connections for a cable.
 * @version 3.0
 * @date 2026-04-01
 *
 * @copyright
 * Dassault Systemes 2025
 *
 */

#pragma once

#include "connector.h"

#include <set>

/**
 * @brief
 * Composite score for a cable-to-cavities allocation.
 *
 * Holds three independent quality metrics:
 *  - compactness : minimum enclosing circle radius of the allocated
 * cavities (↓ better).
 *  - adjacency   : number of Delaunay edges from this allocation's
 * cavities to already-placed cables on the connector (↑ better).
 *                  Zero when no cable has been placed yet (first
 * cable).
 *  - fragments   : number of connected components among remaining
 * available cavities after this allocation is tentatively placed (↓
 * better). A value of 1 means the rest of the connector stays fully
 *                  connected; any value > 1 means isolated pockets
 * would form, which cannot be reached by subsequent cables under
 * mode=1.
 *
 * Lexicographic ordering (best → "less" in std::set):
 *   1. adjacency  descending  — pack against existing bundles
 * first.
 *   2. fragments  ascending   — avoid cutting the remaining space
 * into islands.
 *   3. compactness ascending  — favour tight wire groupings.
 *
 * For the first cable (adjacency=0 for all candidates) fragments
 * becomes the de-facto primary key, naturally preferring peripheral
 * placements that leave the connector contiguous.
 *
 * All three fields are exposed so that a future beam-search pass
 * can score partial placement sequences without recomputing from
 * scratch.
 */
struct AllocationScore
{
    double compactness{0.0}; ///< MEC radius in connector coordinate
                             ///< units (lower = better).
    int adjacency{0};        ///< Edges to already-occupied cavities
                             ///< (higher = better).
    int fragments{1}; ///< Connected components in remaining free
                      ///< cavities (lower = better).

    /**
     * @brief
     * Normalised scalar for display and logging.
     *
     * Formula: compactness * fragments / (1 + adjacency).
     *  - fragments  acts as a multiplier: an isolated-pocket
     * penalty (×1 = no penalty).
     *  - adjacency  acts as a divisor:    rewards touching an
     * existing bundle. When adjacency=0 and fragments=1 (first
     * cable, no fragmentation) this equals the raw MEC radius,
     * preserving backward-compatible behaviour.
     *
     * @return double Combined score (lower = better).
     */
    double combined() const noexcept
    {
        return compactness * static_cast<double>(fragments) /
               (1.0 + static_cast<double>(adjacency));
    }

    /**
     * @brief
     * Strict weak ordering: adjacency desc → fragments asc →
     * compactness asc.
     */
    bool operator<(const AllocationScore& other) const noexcept
    {
        if (adjacency != other.adjacency)
            return adjacency > other.adjacency;
        if (fragments != other.fragments)
            return fragments < other.fragments;
        return compactness < other.compactness;
    }

    bool operator==(const AllocationScore& other) const noexcept
    {
        return adjacency == other.adjacency &&
               fragments == other.fragments &&
               compactness == other.compactness;
    }
};

class cable_allocation
{
    private:

    std::set<int>   _reserved_cavities;
    AllocationScore _score;

    public:

    /**
     * @brief
     * Construct a new cable allocation object
     *
     * @param connections A set that includes the cavities allocated
     * to the cable.
     * @param connector A pointer that points to the cable's target
     * connector.
     *
     * @throw std::runtime_error If connector pointer is expired.
     */
    cable_allocation(
        const std::vector<int>&    connections,
        std::shared_ptr<connector> connector);

    /**
     * @brief
     * Operator< for std::set & std::map.
     *
     * @param other Another cable_allocation object.
     * @return true If reserved_cavities < other's, if equal,
     * compare their score.
     * @return false If they have same reserved cavities.
     */
    bool operator<(const cable_allocation& other) const noexcept;

    /**
     * @brief Get the set of allocated cavityies.
     *
     * @return std::set<int> Allocated cavities for current cable.
     */
    const auto& get_layout() const
    {
        return _reserved_cavities;
    }

    /**
     * @brief Get current allocation's composite score.
     *
     * @return AllocationScore Current allocation's score
     * components.
     */
    const AllocationScore& get_score() const
    {
        return _score;
    }
};