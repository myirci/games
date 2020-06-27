/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "EightPuzzle.hpp"
#include "../utility/Utility.hpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <stack>
#include <utility>

// construct the connectivity graph
const std::array<std::array<unsigned char, 9>,9> EightPuzzle::TileGraph =
{{
     {0,1,0,1,0,0,0,0,0}, // 0
     {1,0,1,0,1,0,0,0,0}, // 1
     {0,1,0,0,0,1,0,0,0}, // 2
     {1,0,0,0,1,0,1,0,0}, // 3
     {0,1,0,1,0,1,0,1,0}, // 4
     {0,0,1,0,1,0,0,0,1}, // 5
     {0,0,0,1,0,0,0,1,0}, // 6
     {0,0,0,0,1,0,1,0,1}, // 7
     {0,0,0,0,0,1,0,1,0}  // 8
 }};

EightPuzzle::EightPuzzle(Board&& b)
{
    m_board = std::move(b);
}

EightPuzzle::EightPuzzle(const Board& b)
{
    std::copy(b.begin(), b.end(), m_board.begin());
}

void EightPuzzle::SetBoard(Board&& b)
{
    m_board = std::move(b);
}

void EightPuzzle::SetBoard(const Board& b)
{
    std::copy(b.begin(), b.end(), m_board.begin());
}

size_t EightPuzzle::GetPosition(uint8_t val) const
{
    return Utility::GetPosition(m_board, val);
}

const EightPuzzle::Board& EightPuzzle::GetBoard() const
{
    return m_board;
}

uint8_t EightPuzzle::GetVal(size_t pos) const
{
    return m_board[pos];
}

bool EightPuzzle::UpdateBoard(size_t pos)
{
    for(auto i = 0; i < 9; i++)
    {
        if(TileGraph[pos][i])
        {
            if(m_board[i] == 0)
            {
                m_board[i] = m_board[pos];
                m_board[pos] = 0;
                return true;
            }
        }
    }
    return false;
}

void EightPuzzle::Shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    do
    {
        std::shuffle(m_board.begin(), m_board.end(), generator);
    } while(!Utility::IsSolvable(m_board));
}

bool EightPuzzle::SolveBFS(Moves& moves, bool graphSearch) const
{
    return graphSearch
            ? SolveBFS_GraphSearch(moves)
            : SolveBFS_TreeSearch(moves);
}

bool EightPuzzle::SolveBFS_TreeSearch(Moves& moves) const
{
    bool solved{false};
    long num_expanded_nodes{0};
    int depthLimit{16};

    std::queue<BoardAndMoves> nodes;
    nodes.emplace(BoardAndMoves(m_board, Moves()));
    while(!nodes.empty())
    {
        BoardAndMoves currentNode = nodes.front();
        if(Utility::IsSolved(currentNode.first))
        {
            std::copy(currentNode.second.begin(), currentNode.second.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        if(currentNode.second.size() > depthLimit)
        {
            break;
        }

        auto nextBoards = Utility::SuccessorBoards(currentNode.first);
        for(auto it = nextBoards.begin(); it != nextBoards.end(); it++)
        {
            BoardAndMoves nd(it->first, currentNode.second);
            nd.second.push_back(it->second);
            nodes.emplace(nd);
        }

        num_expanded_nodes++;
        nodes.pop();
    }

    std::cout << "SolveBFS_TreeSearch: number of expanded nodes is " << num_expanded_nodes << std::endl;
    std::cout << "SolveBFS_TreeSearch: number of nodes remained in the queue is " << nodes.size() << std::endl;

    return solved;
}

bool EightPuzzle::SolveBFS_GraphSearch(Moves& moves) const
{
    bool solved{false};
    long num_expanded_nodes{0};

    std::queue<BoardAndMoves> nodes;
    nodes.emplace(BoardAndMoves(m_board, Moves()));
    HashSet hashSet;

    while(!nodes.empty())
    {
        BoardAndMoves currentNode = nodes.front();
        if(Utility::IsSolved(currentNode.first))
        {
            std::copy(currentNode.second.begin(), currentNode.second.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        auto nextBoards = Utility::SuccessorBoards(currentNode.first);
        for(auto it = nextBoards.begin(); it != nextBoards.end(); it++)
        {
            if(hashSet.find(Utility::GetBoardAsUint(it->first)) == hashSet.end())
            {
                BoardAndMoves nd(it->first, currentNode.second);
                nd.second.push_back(it->second);
                nodes.emplace(nd);
            }
        }

        hashSet.insert(Utility::GetBoardAsUint(currentNode.first));
        nodes.pop();
        num_expanded_nodes++;
    }

    std::cout << "SolveBFS_GraphSearch: number of expanded nodes is " << num_expanded_nodes << std::endl;
    std::cout << "SolveBFS_GraphSearch: number of nodes remained in the queue is " << nodes.size() << std::endl;
    return solved;
}

bool EightPuzzle::SolveNonRecursiveDFS(Moves& moves) const
{
    bool solved = false;
    long num_expanded_nodes{0};

    std::stack<BoardAndMoves> nodes;
    HashSet hashSet;

    nodes.push(BoardAndMoves(m_board, Moves()));
    hashSet.insert(Utility::GetBoardAsUint(m_board));

    while(!nodes.empty())
    {
        if(Utility::IsSolved(nodes.top().first))
        {
            std::copy(nodes.top().second.begin(), nodes.top().second.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        BoardAndMoves currentNode = nodes.top();
        nodes.pop();

        auto nextBoards = Utility::SuccessorBoards(currentNode.first);
        for(auto it = nextBoards.begin(); it != nextBoards.end(); it++)
        {
            if(hashSet.find(Utility::GetBoardAsUint(it->first)) == hashSet.end())
            {
                BoardAndMoves nd(it->first, currentNode.second);
                nd.second.push_back(it->second);
                nodes.emplace(nd);
            }
        }

        num_expanded_nodes++;
        hashSet.insert(Utility::GetBoardAsUint(currentNode.first));
    }

    std::cout << "SolveNonRecursiveDFS: number of expanded nodes is " << num_expanded_nodes << std::endl;
    std::cout << "SolveNonRecursiveDFS: number of nodes remained in the queue is " << nodes.size() << std::endl;

    return solved;
}

bool EightPuzzle::SolveDepthLimitedRecursiveDFS(Moves& moves, bool graphSearch) const
{
    int depthLimit{31};
    auto board = m_board;
    if(graphSearch)
    {
        HashMap hashMap;
        return DepthLimitedRecursiveDFS_GraphSearch(board, hashMap, moves, depthLimit);
    }

    return DepthLimitedRecursiveDFS_TreeSearch(board, moves, depthLimit);
}

bool EightPuzzle::SolveIterativeDeepening(Moves& moves, bool graphSearch) const
{
    int maxDepth = 31;
    int depth = 1;
    auto board = m_board;

    while(depth <= maxDepth)
    {
        if(graphSearch)
        {
            HashMap hashMap;
            auto ret = DepthLimitedRecursiveDFS_GraphSearch(board, hashMap, moves, depth);
            if(ret)
            {
                return true;
            }
        }
        else
        {
            if(DepthLimitedRecursiveDFS_TreeSearch(board, moves, depth))
            {
                return true;
            }
        }

        depth++;
    }

    return false;
}

bool EightPuzzle::SolveUniformCostSearch(Moves& moves) const
{
    bool solved{false};
    long num_expanded_nodes{0};
    auto cmp = [](CNode left, CNode right) { return left.cost > right.cost; };
    std::priority_queue<CNode, std::vector<CNode>, decltype(cmp)> nodes(cmp);
    nodes.emplace(CNode(m_board, 0, {}));
    HashSet hashSet;

    while(!nodes.empty())
    {
        CNode currentNode = nodes.top();
        nodes.pop();
        if(Utility::IsSolved(currentNode.board))
        {
            // update moves
            std::copy(currentNode.moves.begin(), currentNode.moves.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        auto nextBoards = Utility::SuccessorBoards(currentNode.board);
        for(auto it = nextBoards.begin(); it != nextBoards.end(); it++)
        {
            if(hashSet.find(Utility::GetBoardAsUint(it->first)) == hashSet.end())
            {
                CNode nd(it->first, currentNode.cost + it->second, currentNode.moves);
                nd.moves.push_back(it->second);
                nodes.emplace(nd);
            }
        }

        hashSet.insert(Utility::GetBoardAsUint(currentNode.board));
        num_expanded_nodes++;
    }

    std::cout << "SolveUniformCostSearch: number of expanded nodes is " << num_expanded_nodes << std::endl;
    std::cout << "SolveUniformCostSearch: number of nodes remained in the queue is " << nodes.size() << std::endl;
    return solved;
}

bool EightPuzzle::DepthLimitedRecursiveDFS_TreeSearch(Board& board, Moves& moves, int depth) const
{
    if(Utility::IsSolved(board))
    {
        return true;
    }
    else if(depth == 0)
    {
        return false;
    }

    auto emptyPos = Utility::GetPosition(board, 0);
    for(auto i = 0; i < 9; i++)
    {
        if(TileGraph[emptyPos][i] == 0 || (!moves.empty() && board[i] == moves.back()))
        {
            continue;
        }

        // make the move
        board[emptyPos] = board[i];
        board[i] = 0;
        moves.push_back(board[emptyPos]);

        // investigate children
        if(DepthLimitedRecursiveDFS_TreeSearch(board, moves, depth - 1))
        {
            return true;
        }

        // undo the move
        board[i] = board[emptyPos];
        board[emptyPos] = 0;
        moves.pop_back();
    }

    return false;
}

bool EightPuzzle::DepthLimitedRecursiveDFS_GraphSearch(Board& board, HashMap& hashMap, Moves& moves, int depth) const
{
    if(Utility::IsSolved(board))
    {
        return true;
    }
    else if(depth == 0)
    {
        return false;
    }

    auto emptyPos = Utility::GetPosition(board, 0);
    for(auto i = 0; i < 9; i++)
    {
        if(TileGraph[emptyPos][i] == 0)
        {
            continue;
        }

        // make the move
        board[emptyPos] = board[i];
        board[i] = 0;
        moves.push_back(board[emptyPos]);

        // explore the next boards
        auto key = Utility::GetBoardAsUint(board);
        auto it = hashMap.find(key);
        if(it == hashMap.end())
        {
            hashMap.insert({key, depth});
            if(DepthLimitedRecursiveDFS_GraphSearch(board, hashMap, moves, depth - 1))
            {
                return true;
            }
        }
        else
        {
            if(depth > it->second)
            {
                it->second = depth;
                if(DepthLimitedRecursiveDFS_GraphSearch(board, hashMap, moves, depth - 1))
                {
                    return true;
                }
            }
        }

        // undo the move
        board[i] = board[emptyPos];
        board[emptyPos] = 0;
        moves.pop_back();
    }

    return false;
}

bool EightPuzzle::SolveGreedySearch(Moves& moves, int heuristic) const
{
    unsigned int (*g)(const Board& board);
    g = heuristic == 1
            ? Utility::GetNumberOfMisplacedTiles
            : Utility::GetSumOfManhattanDistances;

    bool solved{false};
    long num_expanded_nodes{0};
    auto cmp = [](CNode left, CNode right) { return left.cost > right.cost; };
    std::priority_queue<CNode, std::vector<CNode>, decltype(cmp)> nodes(cmp);
    nodes.emplace(CNode(m_board, g(m_board), {}));
    HashSet hashSet;

    while(!nodes.empty())
    {
        CNode currentNode = nodes.top();
        nodes.pop();

        if(Utility::IsSolved(currentNode.board))
        {
            // update moves
            std::copy(currentNode.moves.begin(), currentNode.moves.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        auto nextBoards = Utility::SuccessorBoards(currentNode.board);
        for(auto it = nextBoards.begin(); it != nextBoards.end(); it++)
        {
            if(hashSet.find(Utility::GetBoardAsUint(it->first)) == hashSet.end())
            {
                CNode nd(it->first, g(it->first), currentNode.moves);
                nd.moves.push_back(it->second);
                nodes.emplace(nd);
            }
        }

        hashSet.insert(Utility::GetBoardAsUint(currentNode.board));
        num_expanded_nodes++;
    }

    std::cout << "SolveGreedySearch: number of expanded nodes is " << num_expanded_nodes << std::endl;
    std::cout << "SolveGreedySearch: number of nodes remained in the queue is " << nodes.size() << std::endl;
    return solved;
}

bool EightPuzzle::SolveAStar(Moves& moves, int heuristic, bool stdMode) const
{
    unsigned int (*h)(const Board& board);
    h = heuristic == 1
            ? Utility::GetNumberOfMisplacedTiles
            : Utility::GetSumOfManhattanDistances;

    bool solved{false};
    long num_expanded_nodes{0};
    auto cmp = [](ANode left, ANode right) { return left.total_cost > right.total_cost; };
    std::priority_queue<ANode, std::vector<ANode>, decltype(cmp)> nodes(cmp);
    nodes.emplace(ANode(m_board, 0, h(m_board), {}));
    HashSet hashSet;

    while(!nodes.empty())
    {
        ANode currentNode = nodes.top();
        nodes.pop();

        if(Utility::IsSolved(currentNode.board))
        {
            // update moves
            std::copy(currentNode.moves.begin(), currentNode.moves.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        auto nextBoards = Utility::SuccessorBoards(currentNode.board);
        for(auto it = nextBoards.begin(); it != nextBoards.end(); it++)
        {
            if(hashSet.find(Utility::GetBoardAsUint(it->first)) == hashSet.end())
            {
                auto cost = stdMode ? (currentNode.cost + 1) : (currentNode.cost + it->second);
                ANode nd(it->first, cost, h(it->first), currentNode.moves);
                nd.moves.push_back(it->second);
                nodes.emplace(nd);
            }
        }

        hashSet.insert(Utility::GetBoardAsUint(currentNode.board));
        num_expanded_nodes++;
    }

    std::cout << "AStar_GraphSearch: number of expanded nodes is " << num_expanded_nodes << std::endl;
    std::cout << "AStar_GraphSearch: number of nodes remained in the queue is " << nodes.size() << std::endl;

    return solved;
}
