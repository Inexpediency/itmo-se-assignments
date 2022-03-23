#ifndef ITMO_SE_ASSIGNMENTS_CONTAINER_H
#define ITMO_SE_ASSIGNMENTS_CONTAINER_H

template<typename T>
class Container {
public:
    virtual bool isEmpty() = 0;

    virtual size_t getSize() = 0;

    virtual void push(T data) = 0;

    virtual T pop() = 0;

    virtual T remove(int index) = 0;
};

#endif //ITMO_SE_ASSIGNMENTS_CONTAINER_H
