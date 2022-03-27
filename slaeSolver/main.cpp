#include <fstream>
#include <iostream>

#include "GaussSolver.h"

void fillMatrixFromFile(std::istream& is, Matrix& matrix)
{
    for (int i = 0; i < matrix.getRowCount(); i++)
        for (int j = 0; j < matrix.getColumnCount(); j++)
            is >> matrix[i][j];
}

int main(int argc, const char* argv[])
{
    if (argc != 2) {
        std::cout << "You need to provide input file path in the command arguments" << std::endl;

        return 0;
    }

    std::ifstream inputFile(argv[1]);
    if (inputFile.bad()) {
        std::cout << "Invalid input file path" << std::endl;

        return 0;
    }

    int rowCount, columnCount;
    inputFile >> rowCount >> columnCount;

    std::cout << std::scientific << std::setprecision(6);

    Matrix matrix = Matrix(rowCount, columnCount);
    fillMatrixFromFile(inputFile, matrix);
    std::cout << "Input matrix:" << std::endl;
    std::cout << matrix << std::endl;

    auto solver = GaussSolver(matrix);
    try {
        std::cout << "Result: " << std::endl;
        auto solution = solver.solve();
        for (int i = 0; i < solution.size(); i++) {
            std::cout << "x[" << i << "]=" << solution[i] << std::endl;
        }
    } catch (NoSolutionsException& e) {
        std::cout << e.what() << std::endl;
    } catch (InfiniteSolutionsException& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl
              << "Result matrix:" << std::endl;
    std::cout << solver.getMatrix() << std::endl;

    return 0;
}
