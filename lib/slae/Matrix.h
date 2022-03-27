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

class Matrix {
private:
    double** matrix;
    int rowCount;
    int columnCount;

public:
    Matrix(int rowCount, int columnCount);

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

    ~Matrix();

    [[nodiscard]] int getRowCount() const;

    [[nodiscard]] int getColumnCount() const;

    void rearrangeRows(int firstIndex, int secondIndex);

    void multiplyRow(int rowIndex, double multiplier);

    void addMultiplied(int toIndex, int rowIndex, double multiplier);

    double*& operator[](int index);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

private:
    [[nodiscard]] bool isValidRowIndex(int index) const;

    [[nodiscard]] bool isValidColumnIndex(int index) const;
};

#endif // ITMO_SE_ASSIGNMENTS_MATRIX_H
