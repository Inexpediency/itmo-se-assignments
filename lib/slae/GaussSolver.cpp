#include "GaussSolver.h"

GaussSolver::GaussSolver(Matrix& matrix)
    : matrix { matrix }
    , columnIndexSystemRightSide { matrix.getColumnCount() - 1 }
{
}

Matrix& GaussSolver::getMatrix()
{
    return matrix;
}

std::vector<double> GaussSolver::solve()
{
    for (int row = straightStep(); row < matrix.getRowCount(); row++)
        if (matrix[row][columnIndexSystemRightSide] != 0)
            throw NoSolutionsException();

    backStep();

    return extractSolution();
}

std::vector<double> GaussSolver::extractSolution()
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

int GaussSolver::straightStep()
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

void GaussSolver::backStep()
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

int GaussSolver::findFirstNonzeroRowUnder(int startRow, int column)
{
    for (int row = startRow; row < matrix.getRowCount(); row++)
        if (matrix[row][column] != 0)
            return row;

    return -1;
}

int GaussSolver::findFirstNonzeroRowUpper(int startRow, int column)
{
    for (int row = startRow; row >= 0; row--)
        if (matrix[row][column] != 0)
            return row;

    return -1;
}

void GaussSolver::makeZerosUnderElement(int elementRow, int elementColumn)
{
    for (int row = elementRow + 1; row < matrix.getRowCount(); row++)
        if (matrix[row][elementColumn] != 0)
            matrix.addMultiplied(row, elementRow, -1 / matrix[elementRow][elementColumn] * matrix[row][elementColumn]);
}

void GaussSolver::makeZerosUpperElement(int elementRow, int elementColumn)
{
    for (int row = elementRow - 1; row >= 0; row--)
        if (matrix[row][elementColumn] != 0)
            matrix.addMultiplied(row, elementRow, -1 / matrix[elementRow][elementColumn] * matrix[row][elementColumn]);
}
