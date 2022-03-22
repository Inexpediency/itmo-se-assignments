#include "ioutils.h"

template<typename T>
void io::readStrings(Container<T> *container, std::ifstream &inputStream, char separator) {
    std::string name;
    while (std::getline(inputStream, name, separator)) {
        container->pushback(name);
    }
}
