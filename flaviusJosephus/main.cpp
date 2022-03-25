#include <iostream>

#include "FlaviusJosephus.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cout << "You need to provide input file path in the command arguments" << std::endl;

        return 0;
    }

    std::ifstream inputFile(argv[1]);
    if (inputFile.bad()) {
        std::cout << "Invalid input file path" << std::endl;

        return 0;
    }

    List<std::string> names = List<std::string>();
    io::readStrings(&names, inputFile, ' ');
    inputFile.close();

    int startIndex, step;
    std::cin >> startIndex >> step;

    std::cout << names << std::endl;
    FlaviusJosephus problem = FlaviusJosephus(&names, startIndex - 1, step - 1);
    problem.printExecutionSequence(std::cout);

    return 0;
}
