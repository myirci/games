#include <fstream>

#include "Nqueens.h"

Nqueens::Nqueens(size_t problem_size) :
    solved{false},
    num_solutions{0},
    n{problem_size},
    board{vector<int>(n, -1)} { }

Nqueens::Nqueens(vector<int>&& v) :
    solved{false},
    num_solutions{0},
    n{v.size()},
    board{std::move(v)} { }

Nqueens::Nqueens(const vector<int>& v) :
    solved{false},
    num_solutions{0},
    n{v.size()},
    board{v} { }

void Nqueens::Solve(int row, bool keep_solution)
{
    PlaceQueen(row, keep_solution);
    solved = true;
}

void Nqueens::SetQueen(size_t row, int col)
{
    board[row] = col;
}

int Nqueens::GetQueen(size_t row) const
{
    return board[row];
}

size_t Nqueens::GetNumberOfSolutions() const
{
    return num_solutions;
}

void Nqueens::ExportSolutions(const string& path) const
{
    ofstream ofs(path, ios::out);
    if(ofs.is_open())
    {
        for(auto& v : solutions)
        {
            for(auto i = 0; i < v.size(); i++)
            {
                ofs << v[i];
                if(i == v.size() - 1)
                {
                    ofs << endl;
                }
                else
                {
                    ofs << ", ";
                }
            }
        }
    }
    ofs.close();
}

void Nqueens::PlaceQueen(size_t row, bool keep_solution)
{
    // try to place a queen to the given row, iterate through all rows
    for(size_t col = 0; col < n; col++)
    {
        // place the queen
        board[row] = col;

        // check if the current state is a valid state
        if(IsValid(row, col))
        {
            if(row == n - 1)
            {
                num_solutions++;
                if(keep_solution)
                {
                    solutions.push_back(board);
                }
            }
            else
            {
                PlaceQueen(row+1, keep_solution);
            }
        }

        // take back the placed queen
        board[row] = -1;
    }
}

bool Nqueens::IsValid(size_t row, size_t col) const
{
    int sum{static_cast<int>(row) + static_cast<int>(col)},
        diff{static_cast<int>(col) - static_cast<int>(row)};

    for(size_t r = 0; r < row; r++)
    {
        if(board[r] == col || board[r] == diff + r || board[r] == sum - r)
        {
            return  false;
        }
    }
    return true;
}
