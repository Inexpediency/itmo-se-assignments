#ifndef ITMO_SE_ASSIGNMENTS_IOUTILS_H
#define ITMO_SE_ASSIGNMENTS_IOUTILS_H

#include "Container.h"
#include <fstream>

namespace io {
template <typename T>
void readStrings(Container<T>* container, std::ifstream& inputStream, char separator)
{
    std::string name;
    while (std::getline(inputStream, name, separator)) {
        container->push(name);
    }
}
}

#endif // ITMO_SE_ASSIGNMENTS_IOUTILS_H
