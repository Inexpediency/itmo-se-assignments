#include "Matrix.h"

Matrix::Matrix(int rowCount, int columnCount)
    : rowCount { rowCount }
    , columnCount { columnCount }
{
    matrix = new double*[rowCount];
    for (int i = 0; i < rowCount; i++)
        matrix[i] = new double[columnCount];
}

Matrix::~Matrix()
{
    for (int i = 0; i < rowCount; i++)
        delete matrix[i];
    delete matrix;
}

int Matrix::getRowCount() const
{
    return rowCount;
}

int Matrix::getColumnCount() const
{
    return columnCount;
}

void Matrix::rearrangeRows(int firstIndex, int secondIndex)
{
    if (!isValidRowIndex(firstIndex))
        throw InvalidRowIndexException(firstIndex);

    std::swap(matrix[firstIndex], matrix[secondIndex]);
}

void Matrix::multiplyRow(int rowIndex, double multiplier)
{
    if (!isValidRowIndex(rowIndex))
        throw InvalidRowIndexException(rowIndex);

    for (int i = 0; i < columnCount; i++)
        matrix[rowIndex][i] *= multiplier;
}

void Matrix::addMultiplied(int toIndex, int rowIndex, double multiplier)
{
    if (!isValidRowIndex(toIndex))
        throw InvalidRowIndexException(toIndex);

    if (!isValidRowIndex(rowIndex))
        throw InvalidRowIndexException(rowIndex);

    for (int i = 0; i < columnCount; i++)
        matrix[toIndex][i] += matrix[rowIndex][i] * multiplier;
}

double*& Matrix::operator[](int index)
{
    return matrix[index];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rowCount; i++) {
        for (int j = 0; j < m.columnCount; j++)
            os << m.matrix[i][j] << "  ";
        os << "\n";
    }

    return os;
}

bool Matrix::isValidRowIndex(int index) const
{
    return 0 <= index && index < rowCount;
}

bool Matrix::isValidColumnIndex(int index) const
{
    return 0 <= index && index < columnCount;
}
