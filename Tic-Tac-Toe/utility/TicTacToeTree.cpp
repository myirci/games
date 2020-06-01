/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#include "TicTacToeTree.hpp"
#include "../utility/Utility.hpp"

#include <iostream>
#include <algorithm>

TicTacToeTree::TicTacToeTree(): root{nullptr} { }

TicTacToeTree::~TicTacToeTree()
{
    Delete(root);
}

bool TicTacToeTree::IsTreeComputed() const
{
    return root != nullptr;
}

void TicTacToeTree::ComputeTree()
{
    // initialize the game board:
    // player-1 -> 1, player-2 -> 2, empty -> 3
    std::array<int, 9> board;
    std::fill(board.begin(), board.end(), 3);

    // create the root node
    root = new Node(GetKey(board), 0, -1);

    // recursively create the nodes
    Compute(board, root, true);
}

void TicTacToeTree::Compute(std::array<int,9>& b, Node* curr, bool player1)
{
    // check if the current node is a terminal node
    curr->terminal = IsTerminal(b);
    if(curr->terminal != -1)
    {
        curr->score = curr->terminal == 2 ? -1 : curr->terminal;
        switch(curr->score)
        {
        case 0:
            curr->num_draws++;
            break;
        case 1:
            curr->num_p1_wins++;
            break;
        case -1:
            curr->num_p2_wins++;
            break;
        }
        return;
    }

    // create the children
    for(int i = 0; i < 9; i++)
    {
        // if the board position at ith index is occupied, continue
        if(b[i] != 3)
        {
            continue;
        }

        // make the move
        b[i] = player1 ? 1 : 2;

        // create the child
        curr->children.emplace_back(new Node(GetKey(b), curr->depth + 1, i));

        // explore the child
        Compute(b, curr->children.back(), !player1);

        // take-back the move
        b[i] = 3;
    }

    // assign the scores
    auto comp = [](Node* n1, Node* n2) { return n1->score < n2->score; };
    if(curr->IsPlayerOneToMove())
    {
        // choose max score
        auto it = std::max_element(curr->children.begin(), curr->children.end(), comp);
        curr->score = (*it)->score;
    }
    else
    {
        // choose min score
        auto it = std::min_element(curr->children.begin(), curr->children.end(), comp);
        curr->score = (*it)->score;
    }

    // count wins and draws
    for(Node* child : curr->children)
    {
        curr->num_p1_wins += child->num_p1_wins;
        curr->num_p2_wins += child->num_p2_wins;
        curr->num_draws += child->num_draws;
    }
}

// returns -1 for non-terminal states
// return 0 for draws
// returns 1 for player-1 wins
// returns 2 for player-2 wins
int TicTacToeTree::IsTerminal(const std::array<int,9>& b) const
{
    // check rows
    for(int i = 0; i < 9; i+=3)
    {
        if(b[i] != 3 && b[i] == b[1 + i] && b[i] == b[2 + i])
        {
            return b[i];
        }
    }

    // check cols
    for(int i = 0; i < 3; ++i)
    {
        if(b[i] != 3 && b[i] == b[3 + i] && b[i] == b[6 + i])
        {
            return b[i];
        }
    }

    // check diagonals
    if(b[0] != 3 && b[0] == b[4] && b[0] == b[8])
    {
        return b[0];
    }

    if(b[2] != 3 && b[2] == b[4] && b[2] == b[6])
    {
        return b[2];
    }

    return std::any_of(b.begin(), b.end(), [](int s){ return s == 3;}) ? -1 : 0;
}

void TicTacToeTree::Delete(Node*& n)
{
    if(n == nullptr)
    {
        return;
    }

    for(Node* child : n->children)
    {
        Delete(child);
    }

    delete n;
    n = nullptr;
}

std::vector<std::string> TicTacToeTree::GetTreeStatistics() const
{
    int num_nodes {0}, num_player1_wins {0}, num_player2_wins {0}, num_draws{0};
    ComputeStatistics(root, num_nodes, num_player1_wins, num_player2_wins, num_draws);
    int num_terminal_states = num_player1_wins + num_player2_wins + num_draws;
    double p1_win_rate = 100 * (double)num_player1_wins / num_terminal_states;
    double p2_win_rate = 100 * (double)num_player2_wins / num_terminal_states;
    double draw_rate = 100 * (double)num_draws / num_terminal_states;
    return std::vector<std::string>
    {
        "Number of tree nodes: " + std::to_string(num_nodes),
        "Number of terminal nodes: " + std::to_string(num_terminal_states),
        "Number of terminal nodes where player-1 wins: " + std::to_string(num_player1_wins) + "(" + std::to_string(p1_win_rate) + " %)",
        "Number of terminal nodes where player-2 wins: " + std::to_string(num_player2_wins) + "(" + std::to_string(p2_win_rate) + " %)",
        "Number of terminal nodes that are ended in a draw: " + std::to_string(num_draws) + "(" + std::to_string(draw_rate) + " %)"
    };
}

void TicTacToeTree::ComputeStatistics(
        Node* n, int& num_nodes, int& num_player1_wins, int& num_player2_wins, int& num_draws) const
{
    num_nodes++;

    if(n->terminal != -1)
    {
        switch(n->terminal)
        {
        case 0:
            num_draws++;
            break;
        case 1:
            num_player1_wins++;
            break;
        case 2:
            num_player2_wins++;
            break;
        }
        return;
    }

    for(Node* child : n->children)
    {
        ComputeStatistics(child, num_nodes, num_player1_wins, num_player2_wins, num_draws);
    }
}

Node* TicTacToeTree::Find(int key)
{
    return Find(root, key);
}

Node* TicTacToeTree::Find(Node* n, int key)
{
    if(n->key == key)
    {
        return n;
    }

    for(Node* child : n->children)
    {
       auto ret = Find(child, key);
       if( ret != nullptr)
       {
           return ret;
       }
    }

    return nullptr;
}
