/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#pragma once

#include <vector>
#include <array>
#include <string>

struct Node
{
    Node(int k, int d, int m) :
        key{k}, depth{d}, move{m}, score{-2}, terminal{-2},
        num_p1_wins{0}, num_p2_wins{0}, num_draws{0} { }
    int key;
    int depth;
    int terminal;
    int score;
    int num_p1_wins;
    int num_p2_wins;
    int num_draws;
    int move;
    std::vector<Node*> children;
    bool IsPlayerOneToMove() // IsMaxPlayer
    {
        return depth % 2 == 0;
    }
};

class TicTacToeTree
{
public:
    TicTacToeTree();
    virtual ~TicTacToeTree();
    void ComputeTree();
    bool IsTreeComputed() const;
    std::vector<std::string> GetTreeStatistics() const;
    Node* Find(int key);
private:
    Node* root;
    void Compute(std::array<int,9>& b, Node* curr, bool player1);
    int IsTerminal(const std::array<int,9>& b) const;
    void Delete(Node*& n);
    void ComputeStatistics(Node* n, int& num_nodes, int& num_player1_wins, int& num_player2_wins, int& num_draws) const;
    Node* Find(Node* n, int key);
};
