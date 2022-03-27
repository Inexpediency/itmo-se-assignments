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
    explicit GaussSolver(Matrix& matrix);

public:
    Matrix& getMatrix();
    std::vector<double> solve();

private:
    std::vector<double> extractSolution();
    int straightStep();
    void backStep();
    int findFirstNonzeroRowUnder(int startRow, int column);
    int findFirstNonzeroRowUpper(int startRow, int column);
    void makeZerosUnderElement(int elementRow, int elementColumn);
    void makeZerosUpperElement(int elementRow, int elementColumn);
};

#endif // ITMO_SE_ASSIGNMENTS_GAUSSSOLVER_H
