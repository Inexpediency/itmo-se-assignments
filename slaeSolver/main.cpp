#include "GaussSolver.h"
#include "Matrix.h"

int main()
{
    double data[3][4] = {
        { 0, 0, 0, 10 },
        { 1, 0, 2, 3 },
        { 0, 0, 5, 2 }
    };
    auto m = Matrix(data);

    std::cout << m << std::endl;
    auto solver = GaussSolver(m);
    solver.solve();
    std::cout << solver.matrix << std::endl;

    return 0;
}
