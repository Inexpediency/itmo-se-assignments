#ifndef ITMO_SE_ASSIGNMENTS_MATRIX_H
#define ITMO_SE_ASSIGNMENTS_MATRIX_H

#include <iomanip>
#include <iostream>

class InvalidRowIndexException : public std::invalid_argument {
public:
    explicit InvalidRowIndexException(int index)
        : std::invalid_argument("invalid row index=" + std::to_string(index))
    {
    }
};

class InvalidColumnIndexException : public std::invalid_argument {
public:
    explicit InvalidColumnIndexException(int index)
        : std::invalid_argument("invalid column index=" + std::to_string(index))
    {
    }
};

class Matrix {
private:
    double** matrix;
    int rowCount;
    int columnCount;

public:
    Matrix(int rowCount, int columnCount)
        : rowCount { rowCount }
        , columnCount { columnCount }
    {
        matrix = new double*[rowCount];
        for (int i = 0; i < rowCount; i++)
            matrix[i] = new double[columnCount];
    }

    template <size_t rows, size_t cols>
    explicit Matrix(double (&data)[rows][cols])
        : rowCount { rows }
        , columnCount { cols }
    {
        matrix = new double*[rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new double[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                matrix[i][j] = data[i][j];
    }

    ~Matrix()
    {
        for (int i = 0; i < rowCount; i++)
            delete matrix[i];
        delete matrix;
    }

    [[nodiscard]] int getRowCount() const
    {
        return rowCount;
    }

    [[nodiscard]] int getColumnCount() const
    {
        return columnCount;
    }

    void rearrangeRows(int firstIndex, int secondIndex)
    {
        if (!isValidRowIndex(firstIndex))
            throw InvalidRowIndexException(firstIndex);

        std::swap(matrix[firstIndex], matrix[secondIndex]);
    }

    void multiplyRow(int rowIndex, double multiplier)
    {
        if (!isValidRowIndex(rowIndex))
            throw InvalidRowIndexException(rowIndex);

        for (int i = 0; i < columnCount; i++)
            matrix[rowIndex][i] *= multiplier;
    }

    void addMultiplied(int toIndex, int rowIndex, double multiplier)
    {
        if (!isValidRowIndex(toIndex))
            throw InvalidRowIndexException(toIndex);

        if (!isValidRowIndex(rowIndex))
            throw InvalidRowIndexException(rowIndex);

        for (int i = 0; i < columnCount; i++)
            matrix[toIndex][i] += matrix[rowIndex][i] * multiplier;
    }

    double*& operator[](int index)
    {
        return matrix[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m)
    {
        for (int i = 0; i < m.rowCount; i++) {
            for (int j = 0; j < m.columnCount; j++)
                os << m.matrix[i][j] << "  ";
            os << "\n";
        }

        return os;
    }

private:
    [[nodiscard]] bool isValidRowIndex(int index) const
    {
        return 0 <= index && index < rowCount;
    }

    [[nodiscard]] bool isValidColumnIndex(int index) const
    {
        return 0 <= index && index < columnCount;
    }
};

#endif // ITMO_SE_ASSIGNMENTS_MATRIX_H
