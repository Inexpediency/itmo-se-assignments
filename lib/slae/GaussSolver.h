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

// GaussSolver is a class that implements the solution of a system of equations by the Gauss method
class GaussSolver {
private:
    Matrix& matrix;
    int columnIndexSystemRightSide;

public:
    explicit GaussSolver(Matrix& matrix);

public:
    // Returns matrix from GaussSolver
    Matrix& getMatrix();

    // Apply Gauss method to matrix and returns the solution if it is the only one
    std::vector<double> solve();

private:
    // Returns the solution if it is the only one
    std::vector<double> extractSolution();

    // Apply straight step to matrix and returns the line where it ended
    int straightStep();

    // Apply back step to matrix
    void backStep();

    // Returns first nonzero row index in column under `startRow` index or -1
    int findFirstNonzeroRowUnder(int startRow, int column);

    // Returns first nonzero row index in column upper `startRow` index or -1
    int findFirstNonzeroRowUpper(int startRow, int column);

    // Make zeros under element with `elementRow` and `elementColumn` positions
    void makeZerosUnderElement(int elementRow, int elementColumn);

    // Make zeros upper element with `elementRow` and `elementColumn` positions
    void makeZerosUpperElement(int elementRow, int elementColumn);
};

#endif // ITMO_SE_ASSIGNMENTS_GAUSSSOLVER_H
