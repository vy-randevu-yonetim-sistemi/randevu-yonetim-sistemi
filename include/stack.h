#ifndef STACK_H
#define STACK_H

#include "randevu.h"

#include <stdexcept>
#include <utility>

class Stack {
private:
    struct Node {
        Randevu data;
        Node *next;

        explicit Node(Randevu d) : data(std::move(d)), next(nullptr) {}
    };

    Node *topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack();

    void push(const Randevu &item);

    Randevu pop();

    [[nodiscard]] Randevu top() const;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] size_t size() const;
};

#endif
