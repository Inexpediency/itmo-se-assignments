#ifndef ITMO_SE_ASSIGNMENTS_IOUTILS_H
#define ITMO_SE_ASSIGNMENTS_IOUTILS_H

#include <fstream>
#include "Container.h"

namespace io {
    template<typename T>
    void readStrings(Container<T> *container, std::ifstream &inputStream, char separator);
}

#endif //ITMO_SE_ASSIGNMENTS_IOUTILS_H
