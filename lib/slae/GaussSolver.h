#ifndef ITMO_SE_ASSIGNMENTS_GAUSSSOLVER_H
#define ITMO_SE_ASSIGNMENTS_GAUSSSOLVER_H

#include "Matrix.h"

class GaussSolver {
public:
    Matrix& matrix;
    int columnIndexSystemRightSide;

public:
    explicit GaussSolver(Matrix& matrix)
        : matrix { matrix }
        , columnIndexSystemRightSide { matrix.getColumnCount() - 1 }
    {
    }

public:
    void solve()
    {
        straightStep();
    }

private:
    void straightStep()
    {
        int columnIndex = 0;

        for (int rowIndex = 0; rowIndex < matrix.getRowCount(); rowIndex++) {
            auto notNullElement = getFirstNotNullElement(rowIndex, columnIndex);
            columnIndex = notNullElement.second;

            matrix.rearrangeRows(notNullElement.first, rowIndex);
            matrix.multiplyRow(rowIndex, 1 / matrix[rowIndex][columnIndex]);

            makeNullsUnderElement(rowIndex, columnIndex);
        }
    }

    std::pair<int, int> getFirstNotNullElement(int startRowIndex, int startColumnIndex)
    {
        int notNullElementRowIndex;
        for (
            notNullElementRowIndex = isNullColumn(startRowIndex, startColumnIndex);
            notNullElementRowIndex < 0 && startColumnIndex < matrix.getColumnCount();
            notNullElementRowIndex = isNullColumn(startRowIndex, startColumnIndex)) {
            startColumnIndex++;
        }

        return { notNullElementRowIndex, startColumnIndex };
    }

    // returns -1 if column is of null else first row index with not null element
    int isNullColumn(int startRowIndex, int columnIndex)
    {
        for (int rowIndex = startRowIndex; rowIndex < matrix.getRowCount(); rowIndex++)
            if (matrix[rowIndex][columnIndex] != 0)
                return rowIndex;

        return -1;
    }

    void makeNullsUnderElement(int rowIndex, int columnIndex)
    {
        for (int i = rowIndex + 1; i < matrix.getRowCount(); i++) {
            if (matrix[i][columnIndex] != 0) {
                double multiplier = -matrix[i][columnIndex] / matrix[rowIndex][columnIndex];
                matrix.addMultiplied(i, rowIndex, multiplier);
            }
        }
    }
};

#endif // ITMO_SE_ASSIGNMENTS_GAUSSSOLVER_H
