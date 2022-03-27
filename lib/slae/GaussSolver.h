#ifndef ITMO_SE_ASSIGNMENTS_GAUSSSOLVER_H
#define ITMO_SE_ASSIGNMENTS_GAUSSSOLVER_H

#include <vector>

#include "Matrix.h"

struct NoSolutionsException : public std::exception {
    [[nodiscard]] const char* what() const noexcept override
    {
        return "system has no solution";
    }
};

struct InfiniteSolutionsException : public std::exception {
    [[nodiscard]] const char* what() const noexcept override
    {
        return "system has infinite number of solutions";
    }
};

class GaussSolver {
private:
    Matrix& matrix;
    int columnIndexSystemRightSide;

public:
    explicit GaussSolver(Matrix& matrix)
        : matrix { matrix }
        , columnIndexSystemRightSide { matrix.getColumnCount() - 1 }
    {
    }

public:
    Matrix& getMatrix()
    {
        return matrix;
    }

    std::vector<double> solve()
    {
        for (int row = straightStep(); row < matrix.getRowCount(); row++)
            if (matrix[row][columnIndexSystemRightSide] != 0)
                throw NoSolutionsException();

        backStep();

        return extractSolution();
    }

private:
    std::vector<double> extractSolution()
    {
        auto solution = std::vector<double>();

        int row = 0;
        for (int column = 0; column < columnIndexSystemRightSide; column++) {
            if (matrix[row][column] != 1)
                throw InfiniteSolutionsException();

            solution.push_back(matrix[row][columnIndexSystemRightSide]);
            row++;
        }

        return solution;
    }

    int straightStep()
    {
        int row = 0;
        for (int column = 0; column < columnIndexSystemRightSide; column++) {
            int nonzeroRow = findFirstNonzeroRowUnder(row, column);
            if (nonzeroRow == -1)
                continue;

            matrix.rearrangeRows(row, nonzeroRow);
            matrix.multiplyRow(row, 1 / matrix[row][column]);
            makeZerosUnderElement(row, column);

            row++;
        }

        return row;
    }

    void backStep()
    {
        int row = matrix.getRowCount() - 1;
        for (int column = columnIndexSystemRightSide - 1; column >= 0; column--) {
            int nonzeroRow = findFirstNonzeroRowUpper(row, column);
            if (nonzeroRow == -1)
                continue;

            row = nonzeroRow;
            makeZerosUpperElement(row, column);

            row--;
        }
    }

    int findFirstNonzeroRowUnder(int startRow, int column)
    {
        for (int row = startRow; row < matrix.getRowCount(); row++)
            if (matrix[row][column] != 0)
                return row;

        return -1;
    }

    int findFirstNonzeroRowUpper(int startRow, int column)
    {
        for (int row = startRow; row >= 0; row--)
            if (matrix[row][column] != 0)
                return row;

        return -1;
    }

    void makeZerosUnderElement(int elementRow, int elementColumn)
    {
        for (int row = elementRow + 1; row < matrix.getRowCount(); row++)
            if (matrix[row][elementColumn] != 0)
                matrix.addMultiplied(row, elementRow, -1 / matrix[elementRow][elementColumn] * matrix[row][elementColumn]);
    }

    void makeZerosUpperElement(int elementRow, int elementColumn)
    {
        for (int row = elementRow - 1; row >= 0; row--)
            if (matrix[row][elementColumn] != 0)
                matrix.addMultiplied(row, elementRow, -1 / matrix[elementRow][elementColumn] * matrix[row][elementColumn]);
    }
};

#endif // ITMO_SE_ASSIGNMENTS_GAUSSSOLVER_H
