#include "Matrix.h"

int main()
{
    Matrix m = Matrix<int>(2, 2);

    m[1][1] = 3;
    m[0][1] = 1;

    std::cout << m << std::endl;

    return 0;
}
