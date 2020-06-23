/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#pragma once

#include <string>
#include <array>
#include <vector>

namespace Utility
{
    using Board = std::array<uint8_t, 9>;

    std::string GetDateAndTime();
    std::string Join(const std::vector<unsigned int>& vec, char c);

    std::string GetBoardAsString(const Board& board);
    unsigned int GetBoardAsUint(const Board& board);
    void PrintBoard(const Board& board);
    bool IsSolved(const Board& board);
    bool IsSolvable(const Board& board);
    size_t GetPosition(const Board& board, uint8_t val);
    std::vector<std::pair<Board, uint8_t>> SuccessorBoards(const Board& board);
    uint8_t Inversion(const Board& board);

    int GetNumberOfMisplacedTiles(const Board& board);
    int GetSumOfManhattanDistances(const Board& board);
}
