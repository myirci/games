/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "Utility.hpp"
#include "TicTacToeTree.hpp"
#include "../logic/TicTacToe.hpp"

#include <chrono>
#include <sstream>
#include <ctime>
#include <numeric>

std::string GetDateAndTime() {

    using std::chrono::system_clock;
    system_clock::time_point today = system_clock::now();
    std::time_t tt = system_clock::to_time_t(today);
    std::stringstream ss;
    ss << ctime(&tt);
    return ss.str();
}

std::unique_ptr<GameScore> Simulate(long num_sim, const Player& p1, const Player& p2, const std::unique_ptr<TicTacToeTree>& gt)
{
    auto logic = std::make_unique<TicTacToe>();
    auto score = std::make_unique<GameScore>();

    for(int i = 0; i < num_sim; i++)
    {
        logic->Reset();
        int sq{-1};
        Result res = Result::no_result;

        while(res == Result::no_result)
        {
            const Player& player = logic->SideToMove() == 1 ? p1 : p2;
            switch (player.type)
            {
            case PlayerType::Computer_RandomMove:
                sq = logic->MakeRandomMove();
                break;
            case PlayerType::Computer_Logic:
                sq = logic->MakeLogicalMove();
                break;
            case PlayerType::Computer_Perfect:
                sq = logic->MakeGameTreeMove(gt);
                break;
            case PlayerType::Computer_PerfectStochastic:
                sq = logic->MakeStochasticGameTreeMove(gt);
                break;
            case PlayerType::Computer_Minimax:
                sq = logic->MakeMiniMaxMove();
                break;
            case PlayerType::Computer_MinimaxStochastic:
                sq = logic->MakeStochasticMiniMaxMove();
                break;
            case PlayerType::Computer_MonteCarloTreeSearch:
                // Not implemented yet!
                break;
            }
            res = logic->GetResult();
        }

        switch (res)
        {
            case Result::player1_win:
                score->num_player1_wins++;
                break;
            case Result::player2_win:
                score->num_player2_wins++;
                break;
            case Result::draw:
                score->num_draws++;
                break;
        }
    }

    return score;
}

int GetKey(const std::array<int,9>& b)
{
    return std::accumulate(b.begin(), b.end(), 0, [](int sum, int elem) { return sum * 10 + elem; });
}
