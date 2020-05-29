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

class TicTacToe
{
public:

    using Board = std::array <Square, 9>;

    // constructors
    TicTacToe();

    // setters
    void SetBoard(Board&& b);
    void SetBoard(const Board& b);
    void SetSquare(std::uint8_t pos, Square s);
    void Clear();

    // getters
    const Board& GetBoard() const;

    // query
    bool Empty() const;
    Result GetResult() const;

    // intelligence
    int MakeARandomMove(Symbol s);
    int MakeALogicalMove(Symbol s);
    int MakeAPerfectMove(Symbol s, bool max_player);

private:
    Board m_board;
    void print_board() const;
    int max_value(Board& b, Square s);
    int min_value(Board& b, Square s);
    Result get_result(const Board& b) const;
    std::vector<int> get_empty_square_indexes() const;
};
