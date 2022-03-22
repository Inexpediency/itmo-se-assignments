#ifndef ITMO_SE_ASSIGNMENTS_CONTAINER_H
#define ITMO_SE_ASSIGNMENTS_CONTAINER_H

template<typename T>
class Container {
public:
    virtual void pushback(T data) = 0;
};

#endif //ITMO_SE_ASSIGNMENTS_CONTAINER_H
