#ifndef STACK_H
#define STACK_H

#include "randevu.h"

#include <stdexcept>
#include <utility>

class Stack {
private:
   struct Node {
      Randevu data;
      Node* next;

      explicit Node(Randevu d) : data(std::move(d)), next(nullptr) {}
   };

   Node* topNode = nullptr;
   size_t count = 0;

public:
   Stack() = default;
   ~Stack();

   Stack(const Stack&) = delete;
   Stack& operator=(const Stack&) = delete;

   void push(const Randevu& item);
   Randevu pop();

   [[nodiscard]] const Randevu& top() const;
   [[nodiscard]] bool isEmpty() const;
   [[nodiscard]] size_t size() const;
};

#endif // STACK_H