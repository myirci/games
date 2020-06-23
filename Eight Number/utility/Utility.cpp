/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include <iostream>
#include <chrono>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <string>

#include "Utility.hpp"
#include "../logic/EightNumber.hpp"

namespace Utility
{

std::string GetDateAndTime()
{
    using std::chrono::system_clock;
    system_clock::time_point today = system_clock::now();
    std::time_t tt = system_clock::to_time_t(today);
    std::stringstream ss;
    ss << ctime(&tt);
    return ss.str();
}

std::string Join(const std::vector<unsigned int>& vec, char c)
{
    std::stringstream ss;
    std::for_each(vec.begin(), vec.end(), [&ss, c](unsigned int i) { ss << i << c;});
    auto str = ss.str();
    str.pop_back();
    return str;
}

std::string GetBoardAsString(const Board& board)
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

unsigned int GetBoardAsUint(const Board& board)
{
    return (board[0]*100 + board[1]*10 + board[2]) * 1000000 +
           (board[3]*100 + board[4]*10 + board[5]) * 1000    +
            board[6]*100 + board[7]*10 + board[8];
}

void PrintBoard(const Board& board)
{
    std::cout << GetBoardAsString(board) << std::endl;
}

size_t GetPosition(const Board& board, uint8_t val)
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

uint8_t Inversion(const Board& board)
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

bool IsSolved(const Board& board)
{
    return GetBoardAsUint(board) == 123456780;
}

bool IsSolvable(const Board& board)
{
    return (Inversion(board) % 2 == 0);
}

std::vector<std::pair<Board, uint8_t>> SuccessorBoards(const Board& board)
{
    std::vector<std::pair<Board, uint8_t>> next_boards;
    Board current_board = board;
    auto emptyPos = GetPosition(board, 0);
    for(auto i = 0; i < 9; i++)
    {
        if(EightNumber::TileGraph[emptyPos][i] == 0)
        {
            continue;
        }

        current_board[emptyPos] = current_board[i];
        current_board[i] = 0;
        next_boards.emplace_back(std::make_pair(current_board, current_board[emptyPos]));
        current_board[i] = current_board[emptyPos];
        current_board[emptyPos] = 0;
    }

    return next_boards;
}

int GetNumberOfMisplacedTiles(const Board& board)
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

int GetSumOfManhattanDistances(const Board& board)
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

}

