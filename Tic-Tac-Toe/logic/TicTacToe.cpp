/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "TicTacToe.hpp"
#include "../utility/Utility.hpp"
#include "../utility/TicTacToeTree.hpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <utility>

TicTacToe::TicTacToe() : m_board{ Square::e, Square::e, Square::e,
                                  Square::e, Square::e, Square::e,
                                  Square::e, Square::e, Square::e } { }

void TicTacToe::SetBoard(Board&& b)
{
    m_board = std::move(b);
}

void TicTacToe::SetBoard(const Board& b)
{
    std::copy(b.begin(), b.end(), m_board.begin());
}

const TicTacToe::Board& TicTacToe::GetBoard() const
{
    return m_board;
}

void TicTacToe::SetSquare(uint8_t pos, Square s)
{
    m_board[pos] = s;
}

bool TicTacToe::Empty() const
{
    return std::all_of(m_board.begin(), m_board.end(), [](Square s){ return s == Square::e; });
}

Result TicTacToe::GetResult() const
{
    return get_result(m_board);
}

void TicTacToe::Clear()
{
    std::fill(m_board.begin(), m_board.end(), Square::e);
}

void TicTacToe::print_board() const {

    for(int i = 0; i < 9; ++i)
    {
        if(m_board[i] == Square::x)
        {
            std::cout << " x ";
        }
        else if(m_board[i] == Square::o)
        {
            std::cout << " o ";
        }
        else
        {
            std::cout << " - ";
        }

        if(i % 3 == 2)
        {
            std::cout << std::endl;
        }
    }
}

int TicTacToe::MakeRandomMove(Symbol s)
{
    auto empty_squares = get_empty_square_indexes();
    auto engine = std::default_random_engine(std::random_device()());
    std::uniform_int_distribution<int> dist(0, empty_squares.size()-1);
    int sq = dist(engine);
    m_board[empty_squares[sq]] = (s == Symbol::X ? Square::x : Square::o);
    return empty_squares[sq];
}

int TicTacToe::MakeLogicalMove(Symbol s)
{
    Square me = (s == Symbol::X ? Square::x : Square::o);
    Square ot = (s == Symbol::X ? Square::o : Square::x);

    // at the beginning, we start from the middle square, may not be the best strategy
    if(Empty())
    {
        m_board[4] = me;
        return 4;
    }

    // is there a winning move
    for(int j = 0; j < 9; j += 3)
    {
        for(int i = 0; i < 3; ++i)
        {
            if(m_board[i+j] == Square::e && m_board[(i+1)%3 + j] == me && m_board[(i+2)%3 + j] == me)
            {
                m_board[i+j] = me;
                return i+j;
            }
        }
    }

    for(int j = 0; j < 3; ++j)
    {
        for(int i = 0; i < 3; ++i)
        {
            if(m_board[3*i + j] == Square::e && m_board[((i+1)%3)*3 + j] == me && m_board[((i+2)%3)*3 + j] == me)
            {
                m_board[3*i+j] = me;
                return 3*i+j;
            }
        }
    }

    for(int i = 0; i < 3; ++i)
    {
        if(m_board[(i+1)*2] == Square::e && m_board[((i+1)%3 + 1)*2] == me && m_board[((i+2)%3 + 1)*2] == me)
        {
            m_board[(i+1)*2] = me;
            return (i+1)*2;
        }
    }

    for(int i = 0; i < 3; ++i)
    {
        if(m_board[i*4] == Square::e && m_board[((i+1)%3)*4] == me && m_board[((i+2)%3)*4] == me)
        {
            m_board[i*4] = me;
            return i*4;
        }
    }

    // can other win ?
    for(int j = 0; j < 9; j += 3)
    {
        for(int i = 0; i < 3; ++i)
        {
            if(m_board[i+j] == Square::e && m_board[(i+1)%3 + j] == ot && m_board[(i+2)%3 + j] == ot)
            {
                m_board[i+j] = me;
                return i+j;
            }
        }
    }

    for(int j = 0; j < 3; ++j)
    {
        for(int i = 0; i < 3; ++i)
        {
            if(m_board[3*i + j] == Square::e && m_board[((i+1)%3)*3 + j] == ot && m_board[((i+2)%3)*3 + j] == ot)
            {
                m_board[3*i+j] = me;
                return 3*i+j;
            }
        }
    }

    for(int i = 0; i < 3; ++i)
    {
        if(m_board[(i+1)*2] == Square::e && m_board[((i+1)%3 + 1)*2] == ot && m_board[((i+2)%3 + 1)*2] == ot)
        {
            m_board[(i+1)*2] = me;
            return (i+1)*2;
        }
    }

    for(int i = 0; i < 3; ++i)
    {
        if(m_board[i*4] == Square::e && m_board[((i+1)%3)*4] == ot && m_board[((i+2)%3)*4] == ot)
        {
            m_board[i*4] = me;
            return i*4;
        }
    }

    if(m_board[4] == Square::e)
    {
        m_board[4] = me;
        return 4;
    }

    return MakeRandomMove(s);
}

int TicTacToe::MakeGameTreeMove(Symbol s, const std::unique_ptr<TicTacToeTree>& gt)
{
    return 0;
}

int TicTacToe::MakeMiniMaxMove(Symbol s, bool max_player)
{
    auto empty_squares = get_empty_square_indexes();

    Board b = m_board;

    if(empty_squares.empty())
    {
        std::cerr << "Already a terminal state!" << std::endl;
        return -1;
    }

    Square sq = (s == Symbol::X ? Square::x : Square::o);
    std::vector<int> scores(empty_squares.size());

    if(max_player)
    {
        for(int i = 0; i < empty_squares.size(); ++i)
        {
            b[empty_squares[i]] = sq;
            scores[i] = min_value(b, (s == Symbol::X ? Square::o : Square::x));
            b[i] = Square::e;
            if(scores[i] > 0)
            { // first winning move
                m_board[empty_squares[i]] = sq;
                return empty_squares[i];
            }
        }
    }
    else
    {
        for(int i = 0; i < empty_squares.size(); ++i)
        {
            b[empty_squares[i]] = sq;
            scores[i] = max_value(b, (s == Symbol::X ? Square::o : Square::x));
            b[i] = Square::e;
            if(scores[i] < 0)
            { // first winning move
                m_board[empty_squares[i]] = sq;
                return empty_squares[i];
            }
        }
    }

    for(int i = 0; i < empty_squares.size(); ++i)
    {
        if(scores[i] == 0)
        { // first drawing move
            m_board[empty_squares[i]] = sq;
            return empty_squares[i];
        }
    }
    // else a make the fist move, it is losing though
    m_board[empty_squares[0]] = sq;
    return empty_squares[0];

}

int TicTacToe::max_value(Board& b, Square s) {

    // if terminal node is reached
    Result r = get_result(b);
    if(r != Result::no_result)
    {
        if(r == Result::x_win)      return 1;
        else if(r == Result::o_win) return -1;
        else if(r == Result::draw)  return 0;
    }

    int score{-1};
    Square sq = (s == Square::x ? Square::o : Square::x);
    for(int i = 0; i < 9; ++i)
    {
        if(b[i] == Square::e)
        {
            b[i] = s;
            score = std::max(score, min_value(b, sq));
            b[i] = Square::e;
        }
    }
    return score;
}

int TicTacToe::min_value(Board& b, Square s)
{
    // if terminal node is reached
    Result r = get_result(b);
    if(r != Result::no_result)
    {
        if(r == Result::x_win)      return 1;
        else if(r == Result::o_win) return -1;
        else if(r == Result::draw)  return 0;
    }

    int score{1};
    Square sq = (s == Square::x ? Square::o : Square::x);
    for(int i = 0; i < 9; ++i)
    {
        if(b[i] == Square::e)
        {
            b[i] = s;
            score = std::min(score, max_value(b, sq));
            b[i] = Square::e;
        }
    }
    return score;
}

Result TicTacToe::get_result(const Board& b) const
{
    // check rows
    for(int i = 0; i < 9; i+=3)
    {
        if(b[i] != Square::e && b[i] == b[1 + i] && b[i] == b[2 + i])
        {
            return (b[i] == Square::x ? Result::x_win : Result::o_win);
        }
    }

    // check cols
    for(int i = 0; i < 3; ++i)
    {
        if(b[i] != Square::e && b[i] == b[3 + i] && b[i] == b[6 + i])
        {
            return (b[i] == Square::x ? Result::x_win : Result::o_win);
        }
    }

    // check diagonals
    if(b[0] != Square::e && b[0] == b[4] && b[0] == b[8])
    {
        return (b[0] == Square::x ? Result::x_win : Result::o_win);
    }

    if(b[2] != Square::e && b[2] == b[4] && b[2] == b[6])
    {
        return (b[2] == Square::x ? Result::x_win : Result::o_win);
    }

    return std::any_of(b.begin(), b.end(), [](Square s){ return s == Square::e;})
        ? Result::no_result
        : Result::draw;
}

std::vector<int> TicTacToe::get_empty_square_indexes() const
{
    std::vector<int> empty_squares;
    for(int i = 0; i < m_board.size(); i++)
    {
        if(m_board[i] == Square::e)
        {
            empty_squares.push_back(i);
        }
    }
    return empty_squares;
}
