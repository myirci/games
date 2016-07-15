/*
 *
 * Murat Yirci - Copyright 2016
 *
 * Contact: myirci@gmail.com
 *
 *
*/
#include "TicTacToe.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <random>
#include <chrono>
#include <queue>
#include <stack>
#include <utility>

TicTacToe::TicTacToe() : m_board{Square::e, Square::e, Square::e,
                                 Square::e, Square::e, Square::e,
                                 Square::e, Square::e, Square::e} { }

void TicTacToe::SetBoard(Board&& b) {
    m_board = std::move(b);
}

void TicTacToe::SetBoard(const Board& b) {
    std::copy(b.begin(), b.end(), m_board.begin());
}

const TicTacToe::Board& TicTacToe::GetBoard() const {
    return m_board;
}

void TicTacToe::SetSquare(uint8_t pos, Square s) {
    m_board[pos] = s;
}

bool TicTacToe::Empty() const {

    for(int i = 0; i < 9; ++i)
        if(m_board[i] != Square::e)
            return false;
    return true;
}

Result TicTacToe::GetResult() const {

    // check rows
    for(int i = 0; i < 9; i+=3)
        if(m_board[0 + i] == m_board[1 + i] && m_board[0 + i] == m_board[2 + i] && m_board[0 + i] != Square::e)
            return (m_board[0 + i] == Square::x ? Result::x_win : Result::o_win);

    // check cols
    for(int i = 0; i < 3; ++i)
        if(m_board[0 + i] == m_board[3 + i] && m_board[0 + i] == m_board[6 + i] && m_board[0 + i] != Square::e)
            return (m_board[0 + i] == Square::x ? Result::x_win : Result::o_win);

    // check diagonals
    if(m_board[0] == m_board[4] && m_board[0] == m_board[8] && m_board[0] != Square::e)
        return (m_board[0] == Square::x ? Result::x_win : Result::o_win);
    if(m_board[2] == m_board[4] && m_board[0] == m_board[6] && m_board[0] != Square::e)
        return (m_board[0] == Square::x ? Result::x_win : Result::o_win);

    // check if game is ended
    for(int i = 0; i < 9; ++i)
        if(m_board[i] == Square::e)
            return Result::no_result;

    return Result::draw;
}

void TicTacToe::Clear() {
    for(int i = 0; i < 9; ++i)
        m_board[i] = Square::e;
}

void TicTacToe::print_board() const {

    for(int i = 0; i < 9; ++i) {
        if(m_board[i] == Square::x) std::cout << " x ";
        else if(m_board[i] == Square::o) std::cout << " o ";
        else std::cout << " - ";
        if(i % 3 == 2)
            std::cout << std::endl;
    }
}
