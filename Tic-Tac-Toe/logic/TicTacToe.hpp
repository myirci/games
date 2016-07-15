/*
 *
 * Murat Yirci - Copyright 2016
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

enum class Result : std::int8_t {
  no_result,
  x_win,
  o_win,
  draw
};

enum class Square : std::int8_t {
    o = -1,
    e,
    x
};

class TicTacToe {
public:

    using Board = std::array <Square, 9>;

    // constructors
    TicTacToe();

    // setters
    void SetBoard(Board&& b);
    void SetBoard(const Board& b);
    void SetSquare(std::uint8_t pos, Square);
    void Clear();

    // getters
    const Board& GetBoard() const;

    // query
    bool Empty() const;
    Result GetResult() const;

private:
    Board m_board;
    void print_board() const;
};