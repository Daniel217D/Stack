#pragma once

#include <iostream>
#include <Windows.h>

using std::out_of_range;

template<class Type>
class Node {
private:
    Type value;

    Node<Type> *next;

    template<typename> friend
    class Stack;

public:
    Node(Type _value, Node *_next = nullptr) : value(_value), next(_next) {
    }

    ~Node() {
        delete next;
    }

    Node *get_next() {
        return next;
    }

    Type get_value() {
        return value;
    }
};

template<class Type>
class Stack {
private:
    Node<Type> *node = nullptr;

    HANDLE hSemaphore;
    const int cMax = 1;

    void upSemaphore() {
        WaitForSingleObject(hSemaphore, INFINITE);
    }

    void downSemaphore() {
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }

    bool _isEmpty() {
        return node == nullptr;
    }
public:
    Stack() {
        hSemaphore = CreateSemaphore(NULL, cMax, cMax, NULL);
    }

    ~Stack() {
        delete node;
    }

    bool isEmpty() {
        upSemaphore();

        bool result = _isEmpty();

        downSemaphore();

        return result;
    }

    void push(Type value) {
        upSemaphore();

        node = new Node<Type>(value, node);

        downSemaphore();
    }

    Type pop() {
        upSemaphore();

        if (_isEmpty()) {
            downSemaphore();
            throw out_of_range("Deque is empty");
        } else {
            Type value = node->value;
            Node<Type> *temp = node;

            node = node->next;
            temp->next = nullptr;
            delete temp;

            downSemaphore();
            return value;
        }
    }
};
