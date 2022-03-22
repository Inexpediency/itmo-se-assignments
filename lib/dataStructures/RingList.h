#ifndef ITMO_SE_ASSIGNMENTS_RINGLIST_H
#define ITMO_SE_ASSIGNMENTS_RINGLIST_H

#include <iostream>
#include <memory>

#include "Container.h"

namespace ring_list {
    template<typename T>
    class Node {
        std::unique_ptr<Node> next{};
        std::string data{};

        explicit Node(T);
    };

    template<typename T>
    class RingList : public Container<T> {
    private:
        int size{};
        std::unique_ptr<Node<T>> tail;

    public:
        RingList();

        ~RingList();

        [[nodiscard]] int getSize() const;

        [[nodiscard]] bool isEmpty() const;

        void pushback(T data);

        char *deleteNode(int index);

        void print(std::ostream &out, const std::string &separator);

    private:
        static bool isIndexValid(int index);

        std::unique_ptr<Node<T>> get(int index);
    };
}

#endif //ITMO_SE_ASSIGNMENTS_RINGLIST_H
