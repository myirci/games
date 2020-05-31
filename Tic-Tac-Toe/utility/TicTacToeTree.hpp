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
    Node(int k, int d) : key{k}, depth{d}, score{-2}, terminal{-2} { }
    int key;
    int depth;
    int terminal;
    int score;
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

private:
    Node* root;
    void Compute(std::array<int,9>& b, Node* curr, bool player1);
    int GetKey(const std::array<int,9>& b) const;
    int IsTerminal(const std::array<int,9>& b) const;
    void Delete(Node*& n);
    void ComputeStatistics(Node* n, int& num_nodes, int& num_player1_wins, int& num_player2_wins, int& num_draws) const;
};
