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
  x_win,
  o_win,
  draw
};

enum class Square : std::int8_t
{
    o = -1,
    e,
    x
};

enum class Symbol : std::int8_t;
class TicTacToeTree;

class TicTacToe
{
public:

    using Board = std::array <Square, 9>;

    TicTacToe();

    void SetSquare(int pos, Square s);
    void Clear();
    bool Empty() const;
    Result GetResult() const;

    // intelligence
    int MakeRandomMove(Symbol s);
    int MakeLogicalMove(Symbol s);
    int MakeGameTreeMove(Symbol s, const std::unique_ptr<TicTacToeTree>& gt);
    // int MakeMiniMaxMove(Symbol s, bool max_player);

private:
    Board m_board;
    std::vector<int> GetEmptySquareIndexes() const;
};
