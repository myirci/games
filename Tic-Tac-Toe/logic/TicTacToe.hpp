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
#include <cstdint>
#include <memory>

enum class Result : std::int8_t
{
  no_result,
  player1_win,
  player2_win,
  draw
};

class TicTacToeTree;

class TicTacToe
{
public:

    using Board = std::array <int, 9>;

    TicTacToe();

    void Reset();
    bool Empty() const;
    Result GetResult() const;
    int SideToMove() const;

    void Moved(int pos);
    int MakeRandomMove();
    int MakeLogicalMove();
    int MakeGameTreeMove(const std::unique_ptr<TicTacToeTree>& gt);
    int MakeStochasticGameTreeMove(const std::unique_ptr<TicTacToeTree>& gt);
    int MakeStochasticMiniMaxMove();
    int MakeMiniMaxMove();
    int MakeStochasticNegaMaxMove();

private:
    int m_side_to_move;
    Board m_board;
    std::vector<int> GetEmptySquareIndexes() const;
    inline void ToggleSideToMove();
    int GetMiniMaxScore(bool maxPlayer);
    int GetNegaMaxScore(int maxPlayer);
};
