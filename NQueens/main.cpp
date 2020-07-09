#include <iostream>
#include <future>
#include <algorithm>
#include <thread>
#include <numeric>
#include <chrono>

#include "Nqueens.h"

using namespace  std;

void solve_single_core(size_t n, bool export_to_text_file);
void solve_multi_core(size_t n, bool export_to_text_file);

int main(void)
{
    size_t n{5};

    auto start1 = chrono::system_clock::now();
    solve_single_core(n, false);
    auto end1 = chrono::system_clock::now();
    auto elapsed1 = chrono::duration_cast<std::chrono::duration<double>>(end1 - start1).count();
    cout << "Single core version took " << elapsed1 << " seconds" << endl;

    auto start2 = chrono::system_clock::now();
    solve_multi_core(n, false);
    auto end2 = chrono::system_clock::now();
    auto elapsed2 = chrono::duration_cast<std::chrono::duration<double>>(end2 - start2).count();
    cout << "Multi core version took " << elapsed2 << " seconds" << endl;
    return 0;
}

void solve_multi_core(size_t n, bool export_to_text_file)
{
    vector<Nqueens> nqs{n, Nqueens{n}};
    for(size_t i = 0; i < nqs.size(); i++)
    {
        nqs[i].SetQueen(0, static_cast<int>(i));
    }

    vector<future<void>> future_vec1;
    for_each(nqs.begin(), nqs.end(), [export_to_text_file, &future_vec1](auto& nq)
    {
        future_vec1.push_back(async(launch::async, &Nqueens::Solve, &nq, 1, export_to_text_file));
    });
    for_each(future_vec1.begin(), future_vec1.end(), [](auto& ft){ft.wait();});

    cout << "N:\t" << n << "\t"
         << accumulate(nqs.begin(), nqs.end(), 0, [](int s, const auto& nq) { return s+=nq.GetNumberOfSolutions(); })
         << endl;

    if(export_to_text_file)
    {
        vector<future<void>> future_vec2;
        for_each(nqs.begin(), nqs.end(), [n, &future_vec2](auto& nq)
        {
            future_vec2.emplace_back(
                        async(launch::async,
                              &Nqueens::ExportSolutions,
                              nq,
                              to_string(n) + "queens_" + to_string(nq.GetQueen(0)) + ".txt"));
        });
        for_each(future_vec2.begin(), future_vec2.end(), [](auto& ft){ft.wait();});
    }
}

void solve_single_core(size_t n, bool export_to_text_file)
{
    Nqueens nq(n);
    nq.Solve();
    cout << "N:\t" << n << "\t" << nq.GetNumberOfSolutions() << endl;
    if(export_to_text_file)
    {
        nq.ExportSolutions("../data/ " + to_string(n) + "Queens.txt");
    }
}
