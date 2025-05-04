#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "randevu.h"

class Stack {
private:
    struct Node {
        Randevu data;
        Node* next;
        explicit Node(const Randevu& d) : data(d), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack();
    void push(const Randevu& item);
    Randevu pop();
    Randevu top() const;
    bool isEmpty() const;
};

#endif