#pragma once

#include <vector>
#include <string>

using namespace  std;

class Nqueens
{
    size_t n;
    vector<int> board;
    bool solved;
    void PlaceQueen(size_t col, bool keep_solution);
    bool IsValid(size_t row, size_t col) const;
    size_t num_solutions;
    vector<vector<int>> solutions;
public:
    explicit Nqueens(size_t n);
    explicit Nqueens(vector<int>&& v);
    explicit Nqueens(const vector<int>& v);
    void SetQueen(size_t row, int col);
    int GetQueen(size_t row) const;
    void Solve(int row = 0, bool keep_solution = false);
    size_t GetNumberOfSolutions() const;
    void ExportSolutions(const string& path) const;
};
