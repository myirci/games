/*
 *
 * Murat Yirci - Copyright 2016
 *
 * Contact: myirci@gmail.com
 *
 *
*/
#include <chrono>
#include <sstream>
#include <ctime>

#include "Utility.hpp"
#include "../logic/TicTacToe.hpp"

#include <memory>

std::string GetDateAndTime() {

    using std::chrono::system_clock;
    system_clock::time_point today = system_clock::now();
    std::time_t tt = system_clock::to_time_t(today);
    std::stringstream ss;
    ss << ctime(&tt);
    return ss.str();
}

std::unique_ptr<GameScore> Simulate(long num_sim, const Player& p1, const Player& p2)
{
    auto logic = std::make_unique<TicTacToe>();
    auto score = std::make_unique<GameScore>();

    for(int i = 0; i < num_sim; i++)
    {
        bool player1{true};
        logic->Clear();
        int sq{-1};
        Result res = Result::no_result;

        while(res == Result::no_result)
        {
            const Player& side_to_move = player1 ? p1 : p2;
            switch (side_to_move.type)
            {
                case PlayerType::Computer_RandomMove:
                    sq = logic->MakeARandomMove(side_to_move.sym);
                    break;
                case PlayerType::Computer_Logic:
                    sq = logic->MakeALogicalMove(side_to_move.sym);
                    break;
                case PlayerType::Computer_Perfect:
                    break;
            }
            res = logic->GetResult();
            player1 = !player1;
        }

        switch (res)
        {
            case Result::x_win:
                score->num_x_wins++;
                break;
            case Result::o_win:
                score->num_o_wins++;
                break;
            case Result::draw:
                score->num_draws++;
                break;
        }
    }

    return score;
}
