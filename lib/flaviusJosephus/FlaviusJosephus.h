#ifndef ITMO_SE_ASSIGNMENTS_FLAVIOUSJOSEPHUS_H
#define ITMO_SE_ASSIGNMENTS_FLAVIOUSJOSEPHUS_H

#include "ioutils.h"
#include "List.h"

using namespace list;

template<typename T>
class FlaviusJosephus {
private:
    Container<T> *names;
    int startIndex;
    int step;

public:
    FlaviusJosephus(Container<T> *names, int startIndex, int step) : names{names}, startIndex{startIndex}, step{step} {}

    void printExecutionSequence(std::ostream &outputStream) {
        int indexToDelete = startIndex;
        while (!names->isEmpty()) {
            indexToDelete = (indexToDelete + step) % names->getSize();
            T name = names->remove(indexToDelete);
            outputStream << name << std::endl;
        }
    }
};

#endif //ITMO_SE_ASSIGNMENTS_FLAVIOUSJOSEPHUS_H
