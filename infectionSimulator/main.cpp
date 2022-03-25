#include "InfectionSimulator.h"

using namespace infection_simulator;

int main()
{
    std::cout << "Input iterations count: ";
    int iterationsCount = 0;
    std::cin >> iterationsCount;

    InfectionSimulator infectionSimulator = InfectionSimulator();
    for (int i = 0; i < iterationsCount; ++i) {
        std::cout << infectionSimulator;
        infectionSimulator.nextIteration();
    }

    return 0;
}
