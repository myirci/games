#include <iostream>
#include "Nqueens.h"

using namespace  std;
int main(void)
{
    for(size_t i = 4; i < 13; i++)
    {
        Nqueens nq(i);
        nq.Solve();
        cout << "N:\t" << i << "\t" << nq.GetNumberOfSolutions() << endl;
        nq.ExportSolutions("../data/ " + to_string(i) + "Queens.txt");
    }
    return 0;
}
