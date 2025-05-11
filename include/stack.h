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

   ~Stack() {
      while (!isEmpty()) {
         pop();
      }
   }

   Stack(const Stack&) = delete;
   Stack& operator=(const Stack&) = delete;

   void push(const Randevu& item) {
      Node* node = new Node(item);
      node->next = topNode;
      topNode = node;
      ++count;
   }

   Randevu pop() {
      if (isEmpty()) {
         throw std::runtime_error("Stack is empty");
      }

      Node* node = topNode;
      Randevu item = node->data;
      topNode = topNode->next;
      delete node;
      --count;
      return item;
   }

   [[nodiscard]] const Randevu& top() const {
      if (isEmpty()) {
         throw std::runtime_error("Stack is empty");
      }
      return topNode->data;
   }

   [[nodiscard]] bool isEmpty() const {
      return topNode == nullptr;
   }

   [[nodiscard]] size_t size() const {
      return count;
   }
};

#endif // STACK_H