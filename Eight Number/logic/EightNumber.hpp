/*
 *
 * Murat Yirci - Copyright 2020
 *
 * Contact: myirci@gmail.com
 *
 *
*/

#ifndef EIGHT_NUMBER_HPP
#define EIGHT_NUMBER_HPP

#include <string>
#include <array>
#include <vector>
#include <cstdint>
#include <unordered_set>

class EightNumber
{
public:
    using Board = std::array<uint8_t, 9>;
    using Moves = std::vector<uint8_t>;
    using BoardAndMoves = std::pair<Board, Moves>;
    using HashTable = std::unordered_set<unsigned int>;
private:
    static const std::array<Board, 9> m_graph;
    Board m_board;

public:

    EightNumber(Board&& b);
    EightNumber(const Board& b);

    // setters
    void SetBoard(Board&& b);
    void SetBoard(const Board& b);

    // getters
    uint16_t GetValue(size_t pos) const;
    size_t GetPosition(uint8_t val) const;
    const Board& GetBoard() const;
    std::string GetBoardAsString() const;

    // print
    void PrintBoard() const;

    // query
    bool IsSolved() const;
    bool IsSolvable() const;

    // process
    bool UpdateBoard(size_t pos);
    void Shuffle();
    void NextBoards(std::vector<Board>& boards) const;

    // solvers
    bool SolveBFS(Moves& moves) const;
    bool SolveNonRecursiveDFS(Moves& moves) const;
    bool SolveRecursiveDFS(Moves& moves) const;
    bool SolveIterativeDeepening(Moves& moves) const;
    bool SolveAStar(Moves& moves) const;

private:
    inline void PrintBoard(const Board& board) const;
    inline bool IsSolved(const Board& board) const;
    inline bool IsSolvable(const Board& board) const;
    inline size_t GetPosition(const Board& board, uint8_t val) const;
    inline std::string GetBoardAsString(const Board& board) const;
    inline unsigned int GetBoardAsUint(const Board& board) const;
    inline void NextBoards(const Board& board, std::vector<Board>& next) const;
    inline uint8_t Inversion(const Board& board) const;
    bool RecursiveDFSDepthLimit(Board& board, Moves& moves, int depth) const;
    bool RecursiveDFSDepthLimitAndHash(Board& board, HashTable& hashTable, Moves& moves, int depth) const;
};

#endif // EIGHT_NUMBER_HPP
