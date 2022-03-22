#include "RingList.h"

namespace ring_list {
    template<typename T>
    Node<T>::Node(T data) {
        this->data = data;
        this->next = nullptr;
    }

    template<typename T>
    RingList<T>::RingList() {
        this->tail = nullptr;
        this->size = 0;
    }

    template<typename T>
    RingList<T>::~RingList() {
        if (!tail)
            return;

        auto currentNode = tail->next;
        tail->next = nullptr;
        while (currentNode) {
            auto nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    template<typename T>
    int RingList<T>::getSize() const {
        return size;
    }

    template<typename T>
    bool RingList<T>::isEmpty() const {
        return getSize() == 0;
    }

    template<typename T>
    void RingList<T>::pushback(T data) {
        auto node = new Node(data);

        if (this->isEmpty()) {
            node->next = node;
            tail = node;
        } else {
            node->next = tail->next;
            tail->next = node;
            tail = node;
        }

        size++;
    }

    template<typename T>
    char *RingList<T>::deleteNode(int index) {
        if (!isIndexValid(index))
            return nullptr;

        if (!tail->next) {
            char *result = tail->getData();
            delete tail;
            this->tail = nullptr;

            return result;
        }

        auto previousNode = index == 0 ? tail : get(index - 1);
        auto nodeToDelete = previousNode->next;

        previousNode->next = nodeToDelete->next;
        if (nodeToDelete == tail)
            tail = previousNode;

        size--;

        char *result = nodeToDelete->getData();
        delete nodeToDelete;

        return result;
    }

    template<typename T>
    void RingList<T>::print(std::ostream &out, const std::string &separator) {
        if (!this->tail)
            return;

        auto currentNode = this->tail->next;
        do {
            out << currentNode->data << separator;
            currentNode = currentNode->next;
        } while (currentNode != this->tail->next);
        out << std::endl;
    }

    template<typename T>
    bool RingList<T>::isIndexValid(int index) {
        return index >= 0;
    }

    template<typename T>
    std::unique_ptr<Node<T>> RingList<T>::get(int index) {
        if (!isIndexValid(index))
            return std::unique_ptr<Node<T>>(nullptr);

        if (size == 0)
            return std::unique_ptr<Node<T>>(nullptr);

        if (size == 1)
            return tail;

        auto currentNode = tail->next;
        for (int i = 0; i < index; i++)
            currentNode = currentNode->next;

        return currentNode;
    }
}
