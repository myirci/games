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
#include <iterator>
#include <random>
#include <utility>
#include <limits>

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

                if(m_board[i*4] != 3)
                {
                    continue;
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
    int key = GetKey(m_board);
    Node* n = gt->Find(key);
    std::vector<Node*> v;

    int sq {-1};
    if(m_side_to_move == 1)
    {
        // check if there is a winning move for player - 1
        std::copy_if(n->children.begin(), n->children.end(), std::back_inserter(v), [](Node* nd) { return nd->score > 0; });
        if(!v.empty())
        {
            // any winning move can be selected, however we choose the one which has more ways to win
            auto it = std::max_element(v.begin(), v.end(), [](Node* nd1, Node* nd2) { return nd1->num_p1_wins < nd2->num_p1_wins; });
            sq = (*it)->move;
        }
        else
        {
            // no winning move, select a non-losing move which has more potential for a win
            std::copy_if(n->children.begin(), n->children.end(), std::back_inserter(v), [](Node* nd) { return nd->score == 0; });
            if(!v.empty())
            {
                auto it = std::max_element(v.begin(), v.end(), [](Node* nd1, Node* nd2) { return nd1->num_p1_wins < nd2->num_p1_wins; });
                sq = (*it)->move;
            }
            else
            {
                // all moves are loosing, select a move which has more potential for a draw or win
                auto it = std::max_element(n->children.begin(), n->children.end(), [](Node* nd1, Node* nd2) { return (nd1->num_p1_wins + nd1->num_draws) < (nd2->num_p1_wins + nd1->num_draws); });
                sq = (*it)->move;
            }
        }
    }
    else
    {
        // check if there is a winning move for player - 2
        std::copy_if(n->children.begin(), n->children.end(), std::back_inserter(v), [](Node* nd) { return nd->score < 0; });
        if(!v.empty())
        {
            // any winning move can be selected, however we choose the one which has more ways to win
            auto it = std::min_element(v.begin(), v.end(), [](Node* nd1, Node* nd2) { return nd1->num_p2_wins < nd2->num_p2_wins; });
            sq = (*it)->move;
        }
        else
        {
            // no winning move, select a non-losing move which has more potential for a win
            std::copy_if(n->children.begin(), n->children.end(), std::back_inserter(v), [](Node* nd) { return nd->score == 0; });
            if(!v.empty())
            {
                auto it = std::max_element(v.begin(), v.end(), [](Node* nd1, Node* nd2) { return nd1->num_p2_wins < nd2->num_p2_wins; });
                sq = (*it)->move;
            }
            else
            {
                // all moves are loosing, select a move which has more potential for a draw or win
                auto it = std::max_element(n->children.begin(), n->children.end(), [](Node* nd1, Node* nd2) { return (nd1->num_p2_wins + nd1->num_draws) < (nd2->num_p2_wins + nd1->num_draws); });
                sq = (*it)->move;
            }
        }
    }
    m_board[sq] = m_side_to_move;
    ToggleSideToMove();
    return sq;
}

int TicTacToe::MakeStochasticGameTreeMove(const std::unique_ptr<TicTacToeTree>& gt)
{
    int key = GetKey(m_board);
    Node* n = gt->Find(key);
    std::vector<Node*> v;
    int sq {-1};

    auto engine = std::default_random_engine(std::random_device()());
    auto pred = m_side_to_move == 1
            ? [](Node* nd) { return nd->score > 0; }
            : [](Node* nd) { return nd->score < 0; };

    // check if there is a winning move for the current player
    std::copy_if(n->children.begin(), n->children.end(), std::back_inserter(v), pred);
    if(!v.empty())
    {
        // select a random winning move
        std::uniform_int_distribution<int> dist(0, v.size()-1);
        sq = v[dist(engine)]->move;
    }
    else
    {
        // no winning move, select a ramdom non-losing move
        std::copy_if(n->children.begin(), n->children.end(), std::back_inserter(v), [](Node* nd) { return nd->score == 0; });
        if(!v.empty())
        {
            std::uniform_int_distribution<int> dist(0, v.size()-1);
            sq = v[dist(engine)]->move;
        }
        else
        {
            // all moves are loosing, select a random move
            std::uniform_int_distribution<int> dist(0, n->children.size()-1);
            sq = n->children[dist(engine)]->move;
        }
    }

    m_board[sq] = m_side_to_move;
    ToggleSideToMove();
    return sq;
}

int TicTacToe::MakeMiniMaxMove()
{
    // get the empty squares: possible moves
    auto empty_squares = GetEmptySquareIndexes();
    if(empty_squares.empty())
    {
        std::cerr << "Already a terminal state!" << std::endl;
        return -1;
    }

    int win_score = m_side_to_move == 1 ? 1 : -1;

    int sq_draw{-1};

    for(int i = 0; i < empty_squares.size(); ++i)
    {
        // make the move
        m_board[empty_squares[i]] = m_side_to_move;

        // compute the score of the current move for the current player
        auto score = GetMiniMaxScore(m_side_to_move != 1);
        if(score == win_score)
        {
            ToggleSideToMove();
            return empty_squares[i];
        }
        else if(sq_draw == -1 && score == 0)
        {
            sq_draw = empty_squares[i];
        }

        // undo the move
        m_board[empty_squares[i]] = 3;
    }

    if(sq_draw != -1)
    {
        m_board[sq_draw] = m_side_to_move;
        ToggleSideToMove();
        return sq_draw;
    }

    m_board[empty_squares[0]] = m_side_to_move;
    ToggleSideToMove();
    return empty_squares[0];
}

int TicTacToe::MakeStochasticMiniMaxMove()
{
    // get the empty squares: possible moves
    auto empty_squares = GetEmptySquareIndexes();
    if(empty_squares.empty())
    {
        std::cerr << "Already a terminal state!" << std::endl;
        return -1;
    }

    // for each available move, compute a score
    std::vector<int> scores(empty_squares.size());
    for(int i = 0; i < empty_squares.size(); ++i)
    {
        // make the move
        m_board[empty_squares[i]] = m_side_to_move;

        // compute the score of the current move for the current player
        scores[i] = GetMiniMaxScore(m_side_to_move != 1);

        // undo the move
        m_board[empty_squares[i]] = 3;
    }

    auto engine = std::default_random_engine(std::random_device()());
    int sq{-1};
    int ds = m_side_to_move == 1 ? 1 : -1;
    std::vector<int> pos;

    for(int i  = 0; i < scores.size(); i++)
    {
        if(scores[i] == ds)
        {
            pos.push_back(i);
        }
    }

    if(!pos.empty())
    {
        std::uniform_int_distribution<int> dist(0, pos.size()-1);
        sq = empty_squares[pos[dist(engine)]];
    }
    else
    {
        for(int i  = 0; i < scores.size(); i++)
        {
            if(scores[i] == 0)
            {
                pos.push_back(i);
            }
        }

        if(!pos.empty())
        {
            std::uniform_int_distribution<int> dist(0, pos.size()-1);
            sq = empty_squares[pos[dist(engine)]];
        }
        else
        {
            std::uniform_int_distribution<int> dist(0, empty_squares.size()-1);
            sq = empty_squares[dist(engine)];
        }
    }

    m_board[sq] = m_side_to_move;
    ToggleSideToMove();
    return sq;
}

int TicTacToe::GetMiniMaxScore(bool maxPlayer)
{
    // check if a terminal node is reached
    switch (GetResult())
    {
    case Result::player1_win:
        return 1;
    case Result::player2_win:
        return -1;
    case Result::draw:
        return 0;
    default:
        break;
    }

    int score = maxPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    // player val
    auto val = maxPlayer ? 1 : 2;

    // iterate over the board
    for(int i = 0; i < 9; ++i)
    {
        if(m_board[i] != 3)
        {
            continue;
        }

        // make the move
        m_board[i] = val;

        // keep the max/min score of the children based on the player type
        score = maxPlayer
                ? std::max(score, GetMiniMaxScore(false))
                : std::min(score, GetMiniMaxScore(true));

        // undo the move
        m_board[i] = 3;
    }

    return score;
}

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

