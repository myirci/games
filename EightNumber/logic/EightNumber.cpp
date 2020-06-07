/*
 *
 * Murat Yirci - Copyright 2014
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

uint16_t EightNumber::GetValue(size_t pos) const {
    return static_cast<uint16_t>(m_board[pos]);
}

size_t EightNumber::GetPosition(uint8_t val) const
{
    return get_position(m_board, val);
}

const EightNumber::Board& EightNumber::GetBoard() const
{
    return m_board;
}

std::string EightNumber::GetBoardAsString() const
{
    return get_board_as_string(m_board);
}

unsigned int EightNumber::GetBoardAsUnsignedInt() const
{
    return get_board_as_uint(m_board);
}

bool EightNumber::IsSolved() const
{
    return is_solved(m_board);
}

bool EightNumber::IsSolvable() const
{
    return is_solvable(m_board);
}

bool EightNumber::UpdateBoard(size_t pos)
{
    for(size_t i = 0; i < 9; ++i)
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
    next_boards(m_board, next);
}

bool EightNumber::SolveBFS(std::vector<uint8_t>& moves) const
{
    std::queue<Board_and_Moves> nodes;
    std::unordered_set<unsigned int> hash_table;
    bool solved = false;

    // step-1: push the current node to the queue and the hash table
    nodes.push(Board_and_Moves(m_board, std::vector<uint8_t>()));
    hash_table.insert(get_board_as_uint(m_board));

    // step-2: process the nodes in the queue
    while(!nodes.empty()) {

        // step-2-1: get a refrence to the front of the queue
        Board_and_Moves& current_node = nodes.front();

        // step-2-2: check if the current node is a solution
        if(is_solved(current_node.first)) {
            std::copy(current_node.second.begin(), current_node.second.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        // step-2-3: find the empty tile position on the current board
        size_t empty_pos = get_position(current_node.first, 0);

        // step-2-4: generate the next possible nodes
        for(size_t i = 0; i < 9; ++i) {
            if(m_graph[empty_pos][i]) {

                // update the board of the current node
                current_node.first[empty_pos] = current_node.first[i];
                current_node.first[i] = 0;

                // if the current node has not been explored before
                auto ret = hash_table.insert(get_board_as_uint(current_node.first));
                if(ret.second) {

                    // update the move of the current board and push it to the queue
                    current_node.second.push_back(current_node.first[empty_pos]);
                    nodes.push(current_node);

                    // take back the move
                    current_node.second.pop_back();
                }

                // take back the board
                current_node.first[i] = current_node.first[empty_pos];
                current_node.first[empty_pos] = 0;
            }
        }

        // remove the processed node from the queue
        nodes.pop();
    }

    std::cout << "Number of moves: " << moves.size() << std::endl;
    std::cout << "Queue size at the end: " << nodes.size() << std::endl;
    std::cout << "Number of valid nodes explored: " << hash_table.size() << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    return solved;
}

bool EightNumber::SolveDFS(std::vector<uint8_t>& moves) const
{

    bool solved = false;

    std::stack<Board_and_Moves> nodes;
    Board_and_Moves current_node;
    std::unordered_set<unsigned int> hash_table;
    std::pair<std::unordered_set<unsigned int>::iterator, bool> ret;

    // step-1: push the current node to the stack and the hash table
    nodes.push(Board_and_Moves(m_board, std::vector<uint8_t>()));
    hash_table.insert(get_board_as_uint(m_board));

    // step-2: process the nodes in the stack
    while(!nodes.empty())
    {
        // step-2-1: check if the top of the stack is a solution
        if(is_solved(nodes.top().first))
        {
            std::copy(nodes.top().second.begin(), nodes.top().second.end(), std::back_inserter(moves));
            solved = true;
            break;
        }

        //step-2-2: get a copy of the top node and remove it from the stack
        current_node = nodes.top();
        nodes.pop();

        // step-2-3: find the empty tile position in the current board
        size_t empty_pos = get_position(current_node.first, 0);

        // step-2-4: generate the next possible nodes
        for(size_t i = 0; i < 9; ++i)
        {
            if(m_graph[empty_pos][i])
            {
                // update the board of the current node
                current_node.first[empty_pos] = current_node.first[i];
                current_node.first[i] = 0;

                // if the current node has not been explored before
                ret = hash_table.insert(get_board_as_uint(current_node.first));
                if(ret.second)
                {
                    // update the move of the current board and push it to the stack
                    current_node.second.push_back(current_node.first[empty_pos]);
                    nodes.push(current_node);

                    // take back the move
                    current_node.second.pop_back();
                }

                // take back the board
                current_node.first[i] = current_node.first[empty_pos];
                current_node.first[empty_pos] = 0;
            }
        }
    }

    std::cout << "Number of moves: " << moves.size() << std::endl;
    std::cout << "Stack size at the end: " << nodes.size() << std::endl;
    std::cout << "Number of valid nodes explored: " << hash_table.size() << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    return solved;
}

bool EightNumber::SolveRecursiveDFS(std::vector<uint8_t>& moves) const
{

    // Note: This function may crash due to the limited size of the stack.
    //       If crashes, increase the stack size.

    // step-1: generate the first node
    Board_and_Moves node(m_board, std::vector<uint8_t>());

    // step-2: push the current node to the hash_table
    std::unordered_set<unsigned int> hash_table;
    hash_table.insert(get_board_as_uint(node.first));

    // step-3: call the recursive function for the current node
    if(recursive_dfs(node, hash_table))
    {
        std::copy(node.second.begin(), node.second.end(), std::back_inserter(moves));
    }

    std::cout << "Number of moves: " << moves.size() << std::endl;
    std::cout << "Number of valid nodes explored: " << hash_table.size() << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

bool EightNumber::recursive_dfs(Board_and_Moves& node, std::unordered_set<unsigned int>& hash_table) const
{
    static int i = 0;
    std::cout << ++i << " ";

    // step-1: check the base condition, i.e., if the current node is a solution or not
    if(is_solved(node.first)) return true;

    // step-2: find the empty tile position on the current board
    size_t empty_pos = get_position(node.first, 0);

    // step-3: process the possible next nodes
    for(size_t i = 0; i < 9; ++i)
    {
        if(m_graph[empty_pos][i])
        {
            // update the board of the current node
            node.first[empty_pos] = node.first[i];
            node.first[i] = 0;

            // check if the current board has been processed before
            auto ret = hash_table.insert(get_board_as_uint(node.first));
            if(ret.second)
            {
                // update the move of the current node
                node.second.push_back(node.first[empty_pos]);

                // call the recursive function for the current node
                if(recursive_dfs(node, hash_table)) return true;

                // take back move
                node.second.pop_back();
            }

            //restore the board
            node.first[i] = node.first[empty_pos];
            node.first[empty_pos] = 0;
        }
    }
    return false;
}

bool EightNumber::SolveIterativeDeepening(std::vector<uint8_t>& moves) const  {


}

bool EightNumber::SolveAStar(std::vector<uint8_t>& moves) const { }

std::string EightNumber::get_board_as_string(const Board& board) const
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

unsigned int EightNumber::get_board_as_uint(const Board& board) const
{
    return (board[0]*100 + board[1]*10 + board[2]) * 1000000 +
           (board[3]*100 + board[4]*10 + board[5]) * 1000    +
            board[6]*100 + board[7]*10 + board[8];
    // std::string state = get_board_as_string(board);
    // return std::stoul(state);
}

bool EightNumber::is_solved(const Board& board) const
{
    return get_board_as_uint(board) == 123456780;
}

bool EightNumber::is_solvable(const Board& board) const
{
    return (inversion(board) % 2 == 0);
}

void EightNumber::next_boards(const Board& board, std::vector<Board>& next) const
{
    Board current_board = board;
    size_t empty_pos = get_position(board, 0);

    for(size_t i = 0; i < 9; ++i)
    {
        if(m_graph[empty_pos][i])
        {
            current_board[empty_pos] = current_board[i];
            current_board[i] = 0;
            next.push_back(current_board);
            current_board[i] = current_board[empty_pos];
            current_board[empty_pos] = 0;
        }
    }
}

void EightNumber::print_board(const Board& board) const
{
    std::cout << get_board_as_string(board) << std::endl;
}

size_t EightNumber::get_position(const Board& board, uint8_t val) const
{
    for(size_t i = 0; i < 9; ++i)
    {
        if(board[i] == val)
            return i;
    }
    return 9;
}

uint8_t EightNumber::inversion(const Board& board) const
{
    uint8_t count = 0;
    for(size_t i = 0; i < 9; ++i)
    {
        if(board[i] == 0)
            continue;

        for(size_t j = i; j < 9; ++j)
        {
            if(board[j] == 0)
                continue;

            if(board[i] > board[j])
                ++count;
        }
    }
    return count;
}
