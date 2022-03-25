#ifndef ITMO_SE_ASSIGNMENTS_INFECTIONSIMULATOR_H
#define ITMO_SE_ASSIGNMENTS_INFECTIONSIMULATOR_H

#include <iostream>
#include <vector>

namespace infection_simulator {
class Config {
public:
    static constexpr int FIELD_SIZE = 21;
    static constexpr int INFECTED_CELL_LIFETIME = 6;
    static constexpr int PROTECTED_CELL_LIFETIME = 4;
    static constexpr char HEALTHY_CELL_SYMBOL = 'H';
    static constexpr char PROTECTED_CELL_SYMBOL = 'P';
    static constexpr char INFECTED_CELL_SYMBOL = 'I';
};

class Cell {
public:
    virtual ~Cell() = default;

    virtual Cell* nextState();

    virtual bool isInfectable();

    virtual bool isContagious();

    virtual char getSymbol();
};

class InfectionSimulator {
protected:
    static constexpr int fieldSize = Config::FIELD_SIZE;
    Cell* field[fieldSize][fieldSize] {};

public:
    InfectionSimulator();

    ~InfectionSimulator();

    void nextIteration();

    friend std::ostream& operator<<(std::ostream& os, const InfectionSimulator& infectionSimulator);

private:
    void infectNeighbour(int x, int y);

    std::vector<Cell**> getCellNeighbours(int x, int y);
};
}
#endif // ITMO_SE_ASSIGNMENTS_INFECTIONSIMULATOR_H
