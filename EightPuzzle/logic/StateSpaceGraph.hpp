/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#pragma once

#include <memory>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>

struct Node
{
    Node(const std::array<uint8_t, 9>& b, int dtg, int mtg, unsigned int stg);
    std::array<uint8_t, 9> board;
    int dist_to_goal;
    int move_to_goal;
    unsigned int successor_to_goal;
    std::vector<unsigned int> successors;
};

struct WNode : public Node
{
    WNode(const std::array<uint8_t, 9>& b, int dtg, int mtg, int ctg, unsigned int stg);
    int cost_to_goal;
};

class StateSpaceGraph
{
private:
    std::unique_ptr<std::unordered_map<unsigned int, Node>> m_snodes;
    std::unique_ptr<std::unordered_map<unsigned int, WNode>> m_wnodes;
public:
    StateSpaceGraph();
    bool IsStandardEightPuzzleStateSpaceGraphComputed() const;
    bool IsWeightedEightPuzzleStateSpaceGraphComputed() const;
    bool GetPathToGoalState(unsigned int initialKey, std::vector<uint8_t>& moves, bool stdPuzzle) const;
    void ComputeStandardEightPuzzleStateSpaceGraph();
    void ComputeWeightedEightPuzzleStateSpaceGraph_Dijkstra();
    void ComputeWeightedEightPuzzleStateSpaceGraph_UniformCostSearch();
    int ExportStandardEightPuzzleStateSpaceGraph(const std::string& fname) const;
    int ExportWeightedEightPuzzleStateSpaceGraph(const std::string& fname) const;
};
