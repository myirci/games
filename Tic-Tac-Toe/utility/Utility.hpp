/*
 *
 * Murat Yirci - Copyright 2016
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

struct GameScore
{
    long num_x_wins;
    long num_o_wins;
    long num_draws;

    GameScore() : num_x_wins{0}, num_o_wins{0}, num_draws{0} { }

    void clear()
    {
        num_x_wins = 0;
        num_o_wins = 0;
        num_draws = 0;
    }

    void print() const
    {
        std::cout << "x-win: " << num_x_wins << std::endl;
        std::cout << "o-win: " << num_o_wins << std::endl;
        std::cout << "draw: " << num_draws << std::endl;
        std::cout << "-------------------" << std::endl;
    }

    std::string get_res() const
    {
        std::string str =
                "x-win: " + std::to_string(num_x_wins) +
                ", o-win: " + std::to_string(num_o_wins) +
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
    Computer_Minmax
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

std::unique_ptr<GameScore> Simulate(long num_sim, const Player& p1, const Player& p2);


#endif // UTILITY_HPP
