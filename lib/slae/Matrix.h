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

// Matrix over a field of real numbers with defined elementary operations
class Matrix {
private:
    double** matrix;
    int rowCount;
    int columnCount;

public:
    // Initialize empty matrix
    Matrix(int rowCount, int columnCount);

    // Initialize matrix with data from two-dimensional array
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

    // Returns matrix row count
    [[nodiscard]] int getRowCount() const;

    // Returns matrix column count
    [[nodiscard]] int getColumnCount() const;

    // Swaps two rows in matrix
    void rearrangeRows(int firstIndex, int secondIndex);

    // Multiplying a row by a reversible element
    void multiplyRow(int rowIndex, double multiplier);

    // Adds to row with `toIndex` row with `rowIndex` multiplied by the reversible element
    void addMultiplied(int toIndex, int rowIndex, double multiplier);

    // Subscription operator overload
    double*& operator[](int index);

    // Print matrix to `std::ostream`
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

private:
    [[nodiscard]] bool isValidRowIndex(int index) const;

    [[nodiscard]] bool isValidColumnIndex(int index) const;
};

#endif // ITMO_SE_ASSIGNMENTS_MATRIX_H
