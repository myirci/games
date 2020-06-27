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
#include "EightPuzzle.hpp"
#include "../utility/Utility.hpp"

Node::Node(const std::array<uint8_t, 9>& b, int dtg, int mtg, unsigned int stg) :
    board{b},
    dist_to_goal{dtg},
    move_to_goal{mtg},
    successor_to_goal{stg} { }

WNode::WNode(const std::array<uint8_t, 9>& b, int dtg, int mtg, int ctg, unsigned int stg) :
    Node(b,dtg,mtg,stg),
    cost_to_goal{ctg} { }

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
        Node& currentNode = nodes.front();
        cbKey = Utility::GetBoardAsUint(currentNode.board);
        auto successors = Utility::SuccessorBoards(currentNode.board);
        for(auto& s : successors)
        {
            key = Utility::GetBoardAsUint(s.first);
            currentNode.successors.push_back(key);
            if(m_snodes->find(key) == m_snodes->end())
            {
                nodes.emplace(Node{s.first, currentNode.dist_to_goal + 1, s.second, cbKey});
            }
        }
        m_snodes->insert(std::make_pair(cbKey, currentNode));
        nodes.pop();
    }
}

void StateSpaceGraph::ComputeWeightedEightPuzzleStateSpaceGraph()
{
    if(m_wnodes)
    {
        std::cout << "Already computed!" << std::endl;
        return;
    }

    m_wnodes = std::make_unique<std::unordered_map<unsigned int, WNode>>();
    unsigned int key{0}, cbKey{0};
    auto cmp = [](WNode left, WNode right)
    {
        if(left.cost_to_goal > right.cost_to_goal)
        {
            return true;
        }
        else if(left.cost_to_goal == right.cost_to_goal)
        {
            return left.dist_to_goal > right.dist_to_goal;
        }
        return false;
    };
    std::priority_queue<WNode, std::vector<WNode>, decltype(cmp)> nodes(cmp);
    nodes.emplace(WNode(std::array<uint8_t, 9>{1,2,3,4,5,6,7,8,0},0,-1,0,0));

    while(!nodes.empty())
    {
        WNode currentNode = nodes.top();
        nodes.pop();
        cbKey = Utility::GetBoardAsUint(currentNode.board);

        auto successors = Utility::SuccessorBoards(currentNode.board);
        for(auto& s : successors)
        {
            key = Utility::GetBoardAsUint(s.first);
            currentNode.successors.push_back(key);
            if(m_wnodes->find(key) == m_wnodes->end())
            {
                nodes.emplace(WNode(s.first, currentNode.dist_to_goal + 1, s.second, currentNode.cost_to_goal + s.second, cbKey));
            }
        }
        m_wnodes->insert(std::make_pair(cbKey, currentNode));
    }
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
    if(!m_wnodes)
    {
        return -1;
    }
    std::ofstream ofs(fname, std::ofstream::out);
    ofs << "State,DistanceToGoal,CostToGoal,MoveTowardsGoal,SuccessorTowardsGoal,Successors" << std::endl;
    for(auto it = m_wnodes->begin(); it != m_wnodes->end(); it++)
    {
        ofs << it->first << ","
            << it->second.dist_to_goal << ","
            << it->second.cost_to_goal << ","
            << it->second.move_to_goal << ","
            << it->second.successor_to_goal << ","
            << Utility::Join(it->second.successors, '|')
            << std::endl;
    }
    ofs.close();
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
    }
    else
    {
        auto key = initialKey;
        std::unordered_map<unsigned int, WNode>::iterator it;
        do
        {
            it = m_wnodes->find(key);
            if(it == m_wnodes->end())
            {
                return false;
            }
            moves.push_back(it->second.move_to_goal);
            key = it->second.successor_to_goal;
        }
        while(it->second.cost_to_goal != 0);
        moves.pop_back();
    }

    return true;
}
