/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstdint>
#include <string>
#include <iostream>
#include <memory>
#include <array>

class TicTacToeTree;

struct GameScore
{
    long num_player1_wins;
    long num_player2_wins;
    long num_draws;

    GameScore() : num_player1_wins{0}, num_player2_wins{0}, num_draws{0} { }

    void Clear()
    {
        num_player1_wins = 0;
        num_player2_wins = 0;
        num_draws = 0;
    }

    void Print() const
    {
        std::cout << "player1-win: " << num_player1_wins << std::endl;
        std::cout << "player2-win: " << num_player2_wins << std::endl;
        std::cout << "draw: " << num_draws << std::endl;
        std::cout << "-------------------" << std::endl;
    }

    std::string GetResult() const
    {
        std::string str =
                "player1-win: " + std::to_string(num_player1_wins) +
                ", player2-win: " + std::to_string(num_player2_wins) +
                ", draw: " + std::to_string(num_draws);
        return str;
    }
};

enum class PlayerType : std::int8_t
{
    Human,
    Computer_RandomMove,
    Computer_Logic,
    Computer_Perfect,
    Computer_PerfectStochastic,
    Computer_Minimax,
    Computer_MinimaxStochastic,
    Computer_NegamaxStochastic,
    Computer_AlphaBetaStochastic,
    Computer_MonteCarloTreeSearch
};

enum class Symbol : std::int8_t
{
    X,
    O
};

struct Player
{
    Player(const std::string& name_, Symbol sym_, PlayerType type_) :
        name{name_}, sym{sym_}, type{type_} { }
    std::string name;
    Symbol sym;
    PlayerType type;
};

std::string GetDateAndTime();

std::unique_ptr<GameScore> Simulate(long num_sim, const Player& p1, const Player& p2, const std::unique_ptr<TicTacToeTree>& gt);

int GetKey(const std::array<int,9>& b);

#endif // UTILITY_HPP
