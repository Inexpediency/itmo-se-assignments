#include "InfectionSimulator.h"


using namespace infection_simulator;

Cell *Cell::nextState() {
    return nullptr;
}

bool Cell::isInfectable() {
    return true;
}

bool Cell::isContagious() {
    return false;
}

char Cell::getSymbol() {
    return Config::HEALTHY_CELL_SYMBOL;
}

class ProtectedCell : public Cell {
private:
    int lifeTime = Config::PROTECTED_CELL_LIFETIME;
public:
    ~ProtectedCell() override = default;

    Cell *nextState() override {
        if (!lifeTime)
            return new Cell();

        lifeTime--;

        return nullptr;
    }

    bool isInfectable() override {
        return false;
    }

    bool isContagious() override {
        return false;
    }

    char getSymbol() override {
        return Config::PROTECTED_CELL_SYMBOL;
    }
};


class InfectedCell : public Cell {
private:
    int lifeTime = Config::INFECTED_CELL_LIFETIME;
public:
    ~InfectedCell() override = default;

    Cell *nextState() override {
        if (!lifeTime)
            return new ProtectedCell();

        lifeTime--;

        return nullptr;
    }

    bool isInfectable() override {
        return false;
    }

    bool isContagious() override {
        return true;
    }

    char getSymbol() override {
        return Config::INFECTED_CELL_SYMBOL;
    }
};

InfectionSimulator::InfectionSimulator() {
    srand(time(nullptr));

    int middle = fieldSize / 2;
    for (int i = 0; i < fieldSize; i++)
        for (int j = 0; j < fieldSize; j++)
            field[i][j] = i == middle && j == middle ? new InfectedCell : new Cell;
}

InfectionSimulator::~InfectionSimulator() {
    for (auto &cellsInRow: field)
        for (auto &cell: cellsInRow)
            delete cell;
}

void InfectionSimulator::nextIteration() {
    for (int i = 0; i < fieldSize; i++)
        for (int j = 0; j < fieldSize; j++) {
            if (field[i][j]->isContagious())
                infectNeighbour(i, j);

            Cell *mutation = field[i][j]->nextState();
            if (mutation) {
                delete field[i][j];
                field[i][j] = mutation;
            }
        }
}

void InfectionSimulator::infectNeighbour(int x, int y) {
    std::vector<Cell **> neighbours = getCellNeighbours(x, y);
    int startNeighbour = (int) (static_cast<int>(rand()) % neighbours.size());

    for (int i = 0; i < neighbours.size(); i++) {
        int currentNeighbourIndex = (startNeighbour + i) % static_cast<int>(neighbours.size());
        Cell **currentNeighbour = neighbours[currentNeighbourIndex];
        if ((*currentNeighbour)->isInfectable() && (rand() % 2)) {
            delete *currentNeighbour;
            *currentNeighbour = new InfectedCell();

            break;
        }
    }
}

std::vector<Cell **> InfectionSimulator::getCellNeighbours(const int x, const int y) {
    int minX = x == 0 ? x : x - 1;
    int maxX = x == fieldSize - 1 ? x : x + 1;

    int minY = y == 0 ? y : y - 1;
    int maxY = y == fieldSize - 1 ? y : y + 1;

    std::vector<Cell **> neighbours;

    for (int i = minX; i < maxX; i++)
        for (int j = minY; j < maxY; j++)
            neighbours.push_back(&field[i][j]);

    return neighbours;
}

std::ostream &infection_simulator::operator<<(std::ostream &os, const InfectionSimulator &infectionSimulator) {
    for (auto &cellsInRow: infectionSimulator.field) {
        for (auto &cell: cellsInRow)
            os << cell->getSymbol() << "  ";
        os << "\n";
    }
    os << "\n";

    return os;
}
