#pragma once

#include <iostream>

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

public:
    ~Stack() {
        delete node;
    }

    bool is_empty() {
        return node == nullptr;
    }

    void push(Type value) {
        node = new Node<Type>(value, node);
    }

    Type pop() {
        if (is_empty()) {
            throw out_of_range("Deque is empty");
        } else {
            Type value = node->value;
            Node<Type> *temp = node;

            node = node->next;
            temp->next = nullptr;
            delete temp;

            return value;
        }
    }
};
