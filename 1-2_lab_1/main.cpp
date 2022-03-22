#include <iostream>
#include <fstream>

#include "ioutils.h"
#include "RingList.h"

using namespace ring_list;

template<typename T>
class FlaviusJosephus {
private:
    RingList <T> *names;
    int startIndex{};
    int step{};

public:
    FlaviusJosephus(RingList <T> *names, int startIndex, int step) {
        this->names = names;
        this->startIndex = startIndex;
        this->step = step;
    }

    void printExecutionSequence(std::ostream &outputStream) {
        int indexToDelete = startIndex;
        while (!names->isEmpty()) {
            indexToDelete = (indexToDelete + step) % names->getSize();
            T name = names->deleteNode(indexToDelete);
            outputStream << name << std::endl;
        }
    }
};


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

    auto names = ring_list::RingList<std::string>();
    io::readStrings(&names, inputFile, '\n');

    inputFile.close();

    int startIndex, step;
    std::cin >> startIndex >> step;

    names.print(std::cout, " ");

    FlaviusJosephus problem = FlaviusJosephus(&names, startIndex - 1, step - 1);
    problem.printExecutionSequence(std::cout);

    return 0;
}
