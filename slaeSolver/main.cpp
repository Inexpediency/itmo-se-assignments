#include "Matrix.h"

int main()
{
    Matrix m = Matrix(3, 3);

    m[1][1] = 3;
    m[0][1] = 1;
    m[2][2] = 2;

    std::cout << m << std::endl;

    m.rearrangeRows(0, 2);
    std::cout << m << std::endl;

    m.multiplyRow(0, 100);
    std::cout << m << std::endl;

    m.addMultiplied(1, 0, -100);
    std::cout << m << std::endl;

    return 0;
}
