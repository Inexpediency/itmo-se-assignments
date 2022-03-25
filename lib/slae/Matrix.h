#ifndef ITMO_SE_ASSIGNMENTS_MATRIX_H
#define ITMO_SE_ASSIGNMENTS_MATRIX_H

#include <iostream>

#include "vector"

template<typename T>
class Matrix {
private:
    T **matrix;
    int rowCount;
    int columnCount;
public:
    Matrix(int rowCount, int columnCount) : rowCount{rowCount}, columnCount{columnCount} {
        matrix = new T *[rowCount];
        for (int i = 0; i < rowCount; i++)
            matrix[i] = new T[columnCount];
    }

    ~Matrix() {
        for (int i = 0; i < rowCount; i++)
            delete matrix[i];

        delete matrix;
    }

    T *&operator[](int index) {
        return matrix[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) {
        for (int i = 0; i < m.rowCount; i++) {
            for (int j = 0; j < m.columnCount; j++)
                os << m.matrix[i][j] << "  ";
            os << "\n";
        }

        return os;
    }
};

#endif //ITMO_SE_ASSIGNMENTS_MATRIX_H
