/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include <iostream>
#include <fstream>
#include <queue>

#include "StateSpaceGraph.hpp"
#include "EightNumber.hpp"
#include "../utility/Utility.hpp"

Node::Node(const std::array<uint8_t, 9>& b, int dtg, int mtg, unsigned int stg) :
    board{b},
    dist_to_goal{dtg},
    move_to_goal{mtg},
    successor_to_goal{stg} { }

StateSpaceGraph::StateSpaceGraph() :
    m_snodes{nullptr},
    m_wnodes{nullptr} { }

void StateSpaceGraph::ComputeStandardEightPuzzleStateSpaceGraph()
{
    if(m_snodes)
    {
        std::cout << "Already computed!" << std::endl;
        return;
    }

    m_snodes = std::make_unique<std::unordered_map<unsigned int, Node>>();
    unsigned int key{0}, cbKey{0};
    std::queue<Node> nodes;
    nodes.emplace(Node{std::array<uint8_t, 9>{1, 2, 3, 4, 5, 6, 7, 8, 0}, 0, -1, 0});

    while(!nodes.empty())
    {
        Node& current_node = nodes.front();
        cbKey = Utility::GetBoardAsUint(current_node.board);
        auto successors = Utility::SuccessorBoards(current_node.board);
        for(auto& s : successors)
        {
            key = Utility::GetBoardAsUint(s.first);
            current_node.successors.push_back(key);
            if(m_snodes->find(key) == m_snodes->end())
            {
                nodes.emplace(Node{s.first, current_node.dist_to_goal + 1, s.second, cbKey});
            }
        }
        m_snodes->insert(std::make_pair(cbKey, current_node));
        nodes.pop();
    }

    ExportStandardEightPuzzleStateSpaceGraph("StateSpaceGraph.csv");
}

void StateSpaceGraph::ComputeWeightedEightPuzzleStateSpaceGraph()
{

}

int StateSpaceGraph::ExportStandardEightPuzzleStateSpaceGraph(const std::string& fname) const
{
    if(!m_snodes)
    {
        return -1;
    }

    std::ofstream ofs(fname, std::ofstream::out);
    ofs << "State,DistanceToGoal,MoveTowardsGoal,SuccessorTowardsGoal,Successors" << std::endl;
    for(auto it = m_snodes->begin(); it != m_snodes->end(); it++)
    {
        ofs << it->first << ","
            << it->second.dist_to_goal << ","
            << it->second.move_to_goal << ","
            << it->second.successor_to_goal << ","
            << Utility::Join(it->second.successors, '|')
            << std::endl;
    }
    ofs.close();
    return 0;
}

int StateSpaceGraph::ExportWeightedEightPuzzleStateSpaceGraph(const std::string& fname) const
{
    return 0;
}

bool StateSpaceGraph::IsStandardEightPuzzleStateSpaceGraphComputed() const
{
    if(m_snodes)
    {
      return true;
    }
    return false;
}

bool StateSpaceGraph::IsWeightedEightPuzzleStateSpaceGraphComputed() const
{
    if(m_wnodes)
    {
      return true;
    }
    return false;
}

bool StateSpaceGraph::GetPathToGoalState(unsigned int initialKey, std::vector<uint8_t>& moves, bool stdPuzzle) const
{
    if(stdPuzzle)
    {
        auto key = initialKey;
        std::unordered_map<unsigned int, Node>::iterator it;
        do
        {
            it = m_snodes->find(key);
            if(it == m_snodes->end())
            {
                return false;
            }
            moves.push_back(it->second.move_to_goal);
            key = it->second.successor_to_goal;
        }
        while(it->second.dist_to_goal != 0);
        moves.pop_back();
        return true;
    }

    return false;
}
