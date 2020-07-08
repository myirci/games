#pragma once

#include <vector>
#include <string>

using namespace  std;

class Nqueens
{
    size_t n;
    vector<int> board;
    bool solved;
    void PlaceQueen(size_t col);
    bool IsValid(size_t row, size_t col);
    vector<vector<int>> solutions;

public:
    Nqueens(size_t n);
    Nqueens(vector<int>&& v);
    Nqueens(const vector<int>& v);
    void Solve();
    int GetNumberOfSolutions() const;
    void ExportSolutions(const string& path) const;
};
