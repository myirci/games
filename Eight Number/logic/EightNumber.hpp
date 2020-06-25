/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#pragma once

#include <string>
#include <array>
#include <vector>
#include <unordered_set>
#include <unordered_map>

struct CNode
{
    CNode(const std::array<uint8_t, 9>& b, unsigned int c, const std::vector<uint8_t>& mv) :
        board{b}, cost{c}, moves{mv} { }

    unsigned int cost;
    std::array<uint8_t, 9> board;
    std::vector<uint8_t> moves;
};

class EightNumber
{
public:
    using Board = std::array<uint8_t, 9>;
    using Moves = std::vector<uint8_t>;
    using BoardAndMoves = std::pair<Board, Moves>;
    using HashSet = std::unordered_set<unsigned int>;
    using HashMap = std::unordered_map<unsigned int, int>;
    static const std::array<Board, 9> TileGraph;
private:
    Board m_board;
public:

    EightNumber(Board&& b);
    EightNumber(const Board& b);

    void SetBoard(Board&& b);
    void SetBoard(const Board& b);
    const Board& GetBoard() const;
    size_t GetPosition(uint8_t val) const;
    uint8_t GetVal(size_t pos) const;
    bool UpdateBoard(size_t pos);
    void Shuffle();

    // solvers
    bool SolveBFS(Moves& moves, bool graphSearch) const;
    bool SolveNonRecursiveDFS(Moves& moves) const;
    bool SolveDepthLimitedRecursiveDFS(Moves& moves, bool graphSearch) const;
    bool SolveIterativeDeepening(Moves& moves, bool graphSearch) const;
    bool SolveAStar(Moves& moves, int heuristic, bool stdMode) const;
    bool SolveGreedySearch(Moves& moves, int heuristic) const;
    bool SolveUniformCostSearch(Moves& moves) const;
private:
    bool SolveBFS_TreeSearch(Moves& moves) const;
    bool SolveBFS_GraphSearch(Moves& moves) const;
    bool DepthLimitedRecursiveDFS_TreeSearch(Board& board, Moves& moves, int depth) const;
    bool DepthLimitedRecursiveDFS_GraphSearch(Board& board, HashMap& hashMap, Moves& moves, int depth) const;
};
