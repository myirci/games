/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "EightNumber.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <random>
#include <chrono>
#include <queue>
#include <stack>
#include <utility>
#include <cmath>

// construct the connectivity graph
const std::array<std::array<unsigned char, 9>,9>
EightNumber::m_graph =
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

EightNumber::EightNumber(Board&& b)
{
    m_board = std::move(b);
}

EightNumber::EightNumber(const Board& b)
{
    std::copy(b.begin(), b.end(), m_board.begin());
}

void EightNumber::SetBoard(Board&& b)
{
    m_board = std::move(b);
}

void EightNumber::SetBoard(const Board& b)
{
    std::copy(b.begin(), b.end(), m_board.begin());
}

uint16_t EightNumber::GetValue(size_t pos) const
{
    return static_cast<uint16_t>(m_board[pos]);
}

size_t EightNumber::GetPosition(uint8_t val) const
{
    return GetPosition(m_board, val);
}

const EightNumber::Board& EightNumber::GetBoard() const
{
    return m_board;
}

std::string EightNumber::GetBoardAsString() const
{
    return GetBoardAsString(m_board);
}

int EightNumber::GetNumberOfMisplacedTiles() const
{
    return GetNumberOfMisplacedTiles(m_board);
}

int EightNumber::GetSumOfManhattanDistances() const
{
    return GetSumOfManhattanDistances(m_board);
}

bool EightNumber::IsSolved() const
{
    return IsSolved(m_board);
}

bool EightNumber::IsSolvable() const
{
    return IsSolvable(m_board);
}

bool EightNumber::UpdateBoard(size_t pos)
{
    for(size_t i = 0; i < 9; i++)
    {
        if(m_graph[pos][i])
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

void EightNumber::PrintBoard() const
{
    std::cout << GetBoardAsString() << std::endl;
}

void EightNumber::Shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    do
    {
        std::shuffle(m_board.begin(), m_board.end(), generator);
    } while(!IsSolvable());
}

void EightNumber::NextBoards(std::vector<Board>& next) const
{
    NextBoards(m_board, next);
}

bool EightNumber::SolveBFS(Moves& moves, bool graphSearch) const
{
    return graphSearch
            ? SolveBFS_GraphSearch(moves)
            : SolveBFS_TreeSearch(moves);
}

bool EightNumber::SolveBFS_TreeSearch(Moves& moves) const
{
    bool solved{false};
    long num_expanded_nodes{0};
    int depthLimit{16};

    std::queue<BoardAndMoves> nodes;
    nodes.push(BoardAndMoves(m_board, Moves()));
    while(!nodes.empty())
    {
        BoardAndMoves& currentNode = nodes.front();
        if(currentNode.second.size() > depthLimit)
        {
            break;
        }

        if(IsSolved(currentNode.first))
        {
            std::copy(currentNode.second.begin(), currentNode.second.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        auto emptyPos = GetPosition(currentNode.first, 0);
        for(size_t i = 0; i < 9; i++)
        {
            if(m_graph[emptyPos][i] == 0)
            {
                continue;
            }

            // update the current board
            currentNode.first[emptyPos] = currentNode.first[i];
            currentNode.first[i] = 0;
            currentNode.second.push_back(currentNode.first[emptyPos]);

            // add new board to the queue
            nodes.push(currentNode);

            // restore the current board
            currentNode.first[i] = currentNode.first[emptyPos];
            currentNode.first[emptyPos] = 0;
            currentNode.second.pop_back();
        }
        num_expanded_nodes++;
        nodes.pop();
    }

    std::cout << "SolveBFS_TreeSearch: number of expanded nodes is " << num_expanded_nodes << std::endl;
    std::cout << "SolveBFS_TreeSearch: number of nodes remained in the queue is " << nodes.size() << std::endl;

    return solved;
}

bool EightNumber::SolveBFS_GraphSearch(Moves& moves) const
{
    bool solved{false};
    long num_expanded_nodes{0};

    std::queue<BoardAndMoves> nodes;
    nodes.push(BoardAndMoves(m_board, Moves()));
    HashSet hashSet{GetBoardAsUint(m_board)};
    while(!nodes.empty())
    {
        BoardAndMoves& currentNode = nodes.front();
        if(IsSolved(currentNode.first))
        {
            std::copy(currentNode.second.begin(), currentNode.second.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        auto emptyPos = GetPosition(currentNode.first, 0);
        for(auto i = 0; i < 9; i++)
        {
            if(m_graph[emptyPos][i] == 0)
            {
                continue;
            }

            // update the board of the current node
            currentNode.first[emptyPos] = currentNode.first[i];
            currentNode.first[i] = 0;

            // if the current node has not been processed/explored/visited/expanded before
            if(hashSet.insert(GetBoardAsUint(currentNode.first)).second)
            {
                // update the move of the current board and push it to the queue
                currentNode.second.push_back(currentNode.first[emptyPos]);
                nodes.push(currentNode);

                // take back the move
                currentNode.second.pop_back();
            }

            // restore the board
            currentNode.first[i] = currentNode.first[emptyPos];
            currentNode.first[emptyPos] = 0;
        }

        nodes.pop();
        num_expanded_nodes++;
    }

    std::cout << "SolveBFS_GraphSearch: number of expanded nodes is " << num_expanded_nodes << std::endl;
    std::cout << "SolveBFS_GraphSearch: number of nodes remained in the queue is " << nodes.size() << std::endl;
    return solved;
}

bool EightNumber::SolveNonRecursiveDFS(Moves& moves) const
{
    bool solved = false;
    std::stack<BoardAndMoves> nodes;
    BoardAndMoves currentNode;
    HashSet hashSet;

    // step-1: push the current node to the stack and the hash table
    nodes.push(BoardAndMoves(m_board, Moves()));
    hashSet.insert(GetBoardAsUint(m_board));

    // step-2: process the nodes in the stack
    while(!nodes.empty())
    {
        // step-2.1: check if the top of the stack is a solution
        if(IsSolved(nodes.top().first))
        {
            std::copy(nodes.top().second.begin(), nodes.top().second.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        // step-2.2: get a copy of the top node and remove it from the stack
        currentNode = nodes.top();
        nodes.pop();

        // step-2.3: find the empty tile position in the current board
        size_t emptyPos = GetPosition(currentNode.first, 0);

        // step-2.4: generate the next possible nodes
        for(size_t i = 0; i < 9; i++)
        {
            if(m_graph[emptyPos][i] == 0)
            {
                continue;
            }

            // update the board of the current node
            currentNode.first[emptyPos] = currentNode.first[i];
            currentNode.first[i] = 0;

            // if the current node has not been explored/visited/processed before
            if(hashSet.insert(GetBoardAsUint(currentNode.first)).second)
            {
                // update the move of the current board and push it to the stack
                currentNode.second.push_back(currentNode.first[emptyPos]);
                nodes.push(currentNode);

                // take back the move
                currentNode.second.pop_back();
            }

            // restore the board
            currentNode.first[i] = currentNode.first[emptyPos];
            currentNode.first[emptyPos] = 0;
        }
    }

    return solved;
}

bool EightNumber::SolveDepthLimitedRecursiveDFS(Moves& moves, bool withHash) const
{
    int depthLimit{100};
    auto board = m_board;
    if(withHash)
    {
        HashMap hashMap;
        return RecursiveDFSDepthLimitWithHashMap(board, hashMap, moves, depthLimit);
    }

    return RecursiveDFSDepthLimitNoHash(board, moves, depthLimit);
}

bool EightNumber::SolveIterativeDeepening(Moves& moves, bool withHash) const
{
    int maxDepth = 50;
    int depth = 1;

    // push the current node to the hash set
    auto board = m_board;
    while(depth <= maxDepth)
    {
        // step-2: call the recursive function for the current node
        if(withHash)
        {
            HashMap hashMap;
            auto ret = RecursiveDFSDepthLimitWithHashMap(board, hashMap, moves, depth);
            if(ret)
            {
                return true;
            }
        }
        else
        {
            if(RecursiveDFSDepthLimitNoHash(board, moves, depth))
            {
                return true;
            }
        }

        depth++;
    }

    return false;
}

bool EightNumber::RecursiveDFSDepthLimitNoHash(Board& board, Moves& moves, int depth) const
{
    // step-1: check if a terminal node is reached
    // step-1.1: check whether the current node is a solution or not
    if(IsSolved(board))
    {
        return true;
    }
    // step-1.2: check if depth limit is reached
    else if(depth == 0)
    {
        return false;
    }

    // step-2: process the possible next moves
    auto emptyPos = GetPosition(board, 0);
    for(size_t i = 0; i < 9; i++)
    {
        if(m_graph[emptyPos][i] == 0 || (!moves.empty() && board[i] == moves.back()))
        {
            continue;
        }

        // make the move
        board[emptyPos] = board[i];
        board[i] = 0;
        moves.push_back(board[emptyPos]);

        // investigate children
        if(RecursiveDFSDepthLimitNoHash(board, moves, depth - 1))
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

bool EightNumber::RecursiveDFSDepthLimitWithHashSet(Board& board, HashSet& hashSet, Moves& moves, int depth) const
{
    // step-1: check if a terminal node is reached
    // step-1.1: check if the current board is a solution
    if(IsSolved(board))
    {
        return true;
    }
    // step-1.2: check if the depth limit is reached
    else if(depth == 0)
    {
        return false;
    }

    // step-2: process the possible next moves
    auto emptyPos = GetPosition(board, 0);
    for(size_t i = 0; i < 9; i++)
    {
        if(m_graph[emptyPos][i] == 0)
        {
            continue;
        }

        // make the move
        board[emptyPos] = board[i];
        board[i] = 0;
        moves.push_back(board[emptyPos]);

        // explore the next boards
        if(hashSet.insert(GetBoardAsUint(board)).second)
        {
            if(RecursiveDFSDepthLimitWithHashSet(board, hashSet, moves, depth - 1))
            {
                return true;
            }
        }

        // undo the move
        board[i] = board[emptyPos];
        board[emptyPos] = 0;
        moves.pop_back();
    }

    return false;
}

bool EightNumber::RecursiveDFSDepthLimitWithHashMap(Board& board, HashMap& hashMap, Moves& moves, int depth) const
{
    // step-1: check if a terminal node is reached
    // step-1.1: check if the current board is a solution
    if(IsSolved(board))
    {
        return true;
    }
    // step-1.2: check if the depth limit is reached
    else if(depth == 0)
    {
        return false;
    }

    // step-2: process the possible next moves
    auto emptyPos = GetPosition(board, 0);
    for(size_t i = 0; i < 9; i++)
    {
        if(m_graph[emptyPos][i] == 0)
        {
            continue;
        }

        // make the move
        board[emptyPos] = board[i];
        board[i] = 0;
        moves.push_back(board[emptyPos]);

        // explore the next boards
        auto key = GetBoardAsUint(board);
        auto it = hashMap.find(key);
        if(it == hashMap.end())
        {
            hashMap.insert({key, depth});
            if(RecursiveDFSDepthLimitWithHashMap(board, hashMap, moves, depth - 1))
            {
                return true;
            }
        }
        else
        {
            if(depth > it->second)
            {
                it->second = depth;
                if(RecursiveDFSDepthLimitWithHashMap(board, hashMap, moves, depth - 1))
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

bool EightNumber::SolveAStar(Moves& moves) const
{
    return false;
}

std::string EightNumber::GetBoardAsString(const Board& board) const
{
    std::stringstream ss;
    std::for_each(board.begin(),
                  board.end(),
                  [&ss](uint8_t c)
    {
        ss << static_cast<unsigned int>(c);
    });
    return ss.str();
}

unsigned int EightNumber::GetBoardAsUint(const Board& board) const
{
    return (board[0]*100 + board[1]*10 + board[2]) * 1000000 +
           (board[3]*100 + board[4]*10 + board[5]) * 1000    +
            board[6]*100 + board[7]*10 + board[8];
    // std::string state = get_board_as_string(board);
    // return std::stoul(state);
}

bool EightNumber::IsSolved(const Board& board) const
{
    return GetBoardAsUint(board) == 123456780;
}

bool EightNumber::IsSolvable(const Board& board) const
{
    return (Inversion(board) % 2 == 0);
}

void EightNumber::NextBoards(const Board& board, std::vector<Board>& next) const
{
    Board current_board = board;
    size_t emptyPos = GetPosition(board, 0);

    for(size_t i = 0; i < 9; i++)
    {
        if(m_graph[emptyPos][i])
        {
            current_board[emptyPos] = current_board[i];
            current_board[i] = 0;
            next.push_back(current_board);
            current_board[i] = current_board[emptyPos];
            current_board[emptyPos] = 0;
        }
    }
}

void EightNumber::PrintBoard(const Board& board) const
{
    std::cout << GetBoardAsString(board) << std::endl;
}

size_t EightNumber::GetPosition(const Board& board, uint8_t val) const
{
    for(size_t i = 0; i < 9; i++)
    {
        if(board[i] == val)
        {
            return i;
        }
    }
    return 9;
}

uint8_t EightNumber::Inversion(const Board& board) const
{
    uint8_t count = 0;
    for(size_t i = 0; i < 9; i++)
    {
        if(board[i] == 0)
        {
            continue;
        }

        for(size_t j = i; j < 9; ++j)
        {
            if(board[j] == 0)
            {
                continue;
            }

            if(board[i] > board[j])
            {
                ++count;
            }
        }
    }
    return count;
}

int EightNumber::GetNumberOfMisplacedTiles(const Board& board) const
{
    int numMisplaced{0};
    for(int i = 0; i < 8; i++)
    {
        if(board[i] != i+1)
        {
            numMisplaced++;
        }
    }
    return numMisplaced;
}

int EightNumber::GetSumOfManhattanDistances(const Board& board) const
{
    int sum{0};
    for(int i = 0; i < 9; i++)
    {
        if(board[i] == 0)
        {
            continue;
        }
        int num = board[i] - 1;
        sum += std::abs(num/3 - i/3);
        sum += std::abs(num%3 - i%3);
    }
    return sum;
}
