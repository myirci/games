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

TicTacToe::TicTacToe() : m_board{3,3,3,3,3,3,3,3,3}, m_side_to_move{1} { }

int TicTacToe::SideToMove() const
{
    return m_side_to_move;
}

void TicTacToe::Moved(int pos)
{
    m_board[pos] = m_side_to_move;
    ToggleSideToMove();
}

void TicTacToe::Reset()
{
    std::fill(m_board.begin(), m_board.end(), 3);
    m_side_to_move = 1;
}

bool TicTacToe::Empty() const
{
    return std::all_of(m_board.begin(), m_board.end(), [](int val){ return val == 3; });
}

Result TicTacToe::GetResult() const
{
    // check rows
    for(int i = 0; i < 9; i+=3)
    {
        if(m_board[i] != 3 && m_board[i] == m_board[1 + i] && m_board[i] == m_board[2 + i])
        {
            return (m_board[i] == 1 ? Result::player1_win : Result::player2_win);
        }
    }

    // check cols
    for(int i = 0; i < 3; ++i)
    {
        if(m_board[i] != 3 && m_board[i] == m_board[3 + i] && m_board[i] == m_board[6 + i])
        {
            return (m_board[i] == 1 ? Result::player1_win : Result::player2_win);
        }
    }

    // check diagonals
    if(m_board[0] != 3 && m_board[0] == m_board[4] && m_board[0] == m_board[8])
    {
        return (m_board[0] == 1 ? Result::player1_win : Result::player2_win);
    }

    if(m_board[2] != 3 && m_board[2] == m_board[4] && m_board[2] == m_board[6])
    {
        return (m_board[2] == 1 ? Result::player1_win : Result::player2_win);
    }

    return std::any_of(m_board.begin(), m_board.end(), [](int val){ return val == 3;})
        ? Result::no_result
        : Result::draw;
}

int TicTacToe::MakeRandomMove()
{
    auto empty_squares = GetEmptySquareIndexes();
    auto engine = std::default_random_engine(std::random_device()());
    std::uniform_int_distribution<int> dist(0, empty_squares.size()-1);
    int sq = dist(engine);
    m_board[empty_squares[sq]] = m_side_to_move;
    ToggleSideToMove();
    return empty_squares[sq];
}

int TicTacToe::MakeLogicalMove()
{
    int sq1{-1}, sq2{-1};

    // at the beginning, we start from the middle square, may not be the best strategy
    if(Empty())
    {
        sq1 = 4;
    }
    else
    {
        int other = m_side_to_move == 1 ? 2 : 1;

        // rows
        for(int j = 0; j < 9; j += 3)
        {
            for(int i = 0; i < 3; ++i)
            {
                if(m_board[i+j] != 3)
                {
                    continue;
                }

                if(m_board[(i+1)%3 + j] == m_side_to_move && m_board[(i+2)%3 + j] == m_side_to_move)
                {
                    sq1 = i+j;
                }
                else if(m_board[(i+1)%3 + j] == other && m_board[(i+2)%3 + j] == other)
                {
                    sq2 = i+j;
                }
            }
        }

        // columns
        if(sq1 == -1)
        {
            for(int j = 0; j < 3; ++j)
            {
                for(int i = 0; i < 3; ++i)
                {
                    if(m_board[3*i + j] != 3)
                    {
                        continue;
                    }

                    if(m_board[((i+1)%3)*3 + j] == m_side_to_move && m_board[((i+2)%3)*3 + j] == m_side_to_move)
                    {
                        sq1 = 3*i+j;
                    }
                    else if(m_board[((i+1)%3)*3 + j] == other && m_board[((i+2)%3)*3 + j] == other)
                    {
                        sq2 = 3*i+j;
                    }
                }
            }
        }

        // diagonals
        if(sq1 == -1)
        {
            for(int i = 0; i < 3; ++i)
            {
                if(m_board[(i+1)*2] != 3)
                {
                    continue;
                }

                if(m_board[((i+1)%3 + 1)*2] == m_side_to_move && m_board[((i+2)%3 + 1)*2] == m_side_to_move)
                {
                    sq1 = (i+1)*2;
                }
                else if(m_board[((i+1)%3 + 1)*2] == other && m_board[((i+2)%3 + 1)*2] == other)
                {
                    sq2 = (i+1)*2;
                }

                if(m_board[((i+1)%3)*4] == m_side_to_move && m_board[((i+2)%3)*4] == m_side_to_move)
                {
                    sq1 = i*4;
                }
                else if(m_board[((i+1)%3)*4] == other && m_board[((i+2)%3)*4] == other)
                {
                    sq2 = i*4;
                }
            }
        }
    }

    int sq = sq1 != -1 ? sq1 : sq2;
    if(sq != -1)
    {
        m_board[sq] = m_side_to_move;
        ToggleSideToMove();
        return sq;
    }

    return MakeRandomMove();
}

int TicTacToe::MakeGameTreeMove(const std::unique_ptr<TicTacToeTree>& gt)
{
    return 0;
}

/*
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
*/

std::vector<int> TicTacToe::GetEmptySquareIndexes() const
{
    std::vector<int> empty_squares;
    for(int i = 0; i < m_board.size(); i++)
    {
        if(m_board[i] == 3)
        {
            empty_squares.push_back(i);
        }
    }
    return empty_squares;
}

void TicTacToe::ToggleSideToMove()
{
    m_side_to_move = (m_side_to_move == 1 ? 2 : 1);
}

