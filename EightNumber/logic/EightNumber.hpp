/*
 *
 * Murat Yirci - Copyright 2014
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

class EightNumber {
public:
    typedef std::array<uint8_t, 9> Board;
    typedef std::pair<Board, std::vector<uint8_t>> Board_and_Moves;
private:
    static const std::array<Board, 9> m_graph;
    Board m_board;

public:
    // constructors
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
    unsigned int GetBoardAsUnsignedInt() const;

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
    bool SolveBFS(std::vector<uint8_t>& moves) const;
    bool SolveDFS(std::vector<uint8_t>& moves) const ;
    bool SolveRecursiveDFS(std::vector<uint8_t>& moves) const;
    bool SolveIterativeDeepening(std::vector<uint8_t>& moves) const;
    bool SolveAStar(std::vector<uint8_t>& moves) const;

private:
    inline void print_board(const Board& board) const;
    inline bool is_solved(const Board& board) const;
    inline bool is_solvable(const Board& board) const;
    inline size_t get_position(const Board& board, uint8_t val) const;
    inline std::string get_board_as_string(const Board& board) const;
    inline unsigned int get_board_as_uint(const Board& board) const;
    inline void next_boards(const Board& board, std::vector<Board>& next) const;
    inline uint8_t inversion(const Board& board) const;
    bool recursive_dfs(Board_and_Moves& node, std::unordered_set<unsigned int>& hash_table) const;
};

#endif // EIGHT_NUMBER_HPP
