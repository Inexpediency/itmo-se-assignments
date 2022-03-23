#ifndef ITMO_SE_ASSIGNMENTS_LIST_H
#define ITMO_SE_ASSIGNMENTS_LIST_H

#include <iostream>
#include <memory>

#include "Container.h"

namespace list {

    template<typename T>
    struct Node {
        T data;
        std::unique_ptr<Node<T>> next;

        explicit Node(T data) : data{data}, next{nullptr} {}
    };

    template<typename T>
    class List : public Container<T> {
    private:
        size_t size;
        std::unique_ptr<Node<T>> head{};
    public:
        List() : head{nullptr}, size{0} {};

        List(const List &list) : size{list.size} {
            Node<T> *root = list.head.get();

            std::unique_ptr<Node<T>> new_head{nullptr};
            Node<T> *pnew_head{nullptr};
            while (root) {
                auto temp{std::make_unique<Node>(root->data)};
                if (new_head == nullptr) {
                    new_head = std::move(temp);
                    pnew_head = new_head.get();
                } else {
                    pnew_head->next = std::move(temp);
                    pnew_head = pnew_head->next.get();
                }
                root = root->next.get();
            }
            head = std::move(new_head);
        }

        List(List &&list) noexcept: size{list.size} {
            head = std::move(list.head);
        }

        ~List() {
            clean();
        }

        size_t getSize() {
            return this->size;
        }

        bool isEmpty() {
            return getSize() == 0;
        }

        void push(T data) {
            auto temp{std::make_unique<Node<T>>(data)};
            if (head) {
                temp->next = std::move(head);
            }
            head = std::move(temp);

            size++;
        }

        T pop() {
            if (head == nullptr) {
                return T();
            }

            T data = head->data;
            std::unique_ptr<Node<T>> temp = std::move(head);
            head = std::move(temp->next);

            size--;

            return data;
        }

        T remove(int index) {
            if ((head == nullptr) || !isIndexValid(index))
                return T();

            Node<T> *temp = head.get();

            if (index == 0) {
                T data = temp->data;
                head = std::move(temp->next);
                size--;

                return data;
            }

            for (int i = 0; i < index - 1; i++)
                temp = temp->next.get();

            T data = temp->next->data;
            temp->next = std::move(temp->next->next);

            size--;

            return data;
        }

        void clean() {
            while (head) {
                head = std::move(head->next);
            }
        }

        void reverse() {
            List tmp;
            Node<T> *root = head.get();
            while (root) {
                tmp.push(root->data);
                root = root->next.get();
            }
            clean();
            head = std::move(tmp.head);
        }

        friend std::ostream &operator<<(std::ostream &os, const List &list) {
            Node<T> *currentNode = list.head.get();
            while (currentNode) {
                os << currentNode->data << ' ';
                currentNode = currentNode->next.get();
            }
            return os;
        }

    private:
        bool isIndexValid(int index) {
            return index >= 0 && index < size;
        }
    };
}

#endif //ITMO_SE_ASSIGNMENTS_LIST_H
