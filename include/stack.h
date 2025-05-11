#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include <utility>

template<typename T>
class Stack {
private:
   struct Node {
      T data;
      Node *next;

      explicit Node(T d) : data(std::move(d)), next(nullptr) {}
   };

   Node *topNode = nullptr;
   size_t count = 0;

public:
   Stack() = default;

   Stack(const Stack &other) {
      if (other.topNode == nullptr) return;

      Stack<T> reverseTemp;
      for (Node *current = other.topNode; current != nullptr; current = current->next) {
         reverseTemp.push(current->data);
      }

      while (!reverseTemp.isEmpty()) {
         push(reverseTemp.pop());
      }
   }

   Stack &operator=(const Stack &) = delete;

   ~Stack() {
      while (!isEmpty()) {
         pop();
      }
   }

   void push(const T &item) {
      Node *node = new Node(item);
      node->next = topNode;
      topNode = node;
      ++count;
   }

   T pop() {
      if (isEmpty()) {
         throw std::runtime_error("Stack is empty");
      }

      Node *node = topNode;
      T item = node->data;
      topNode = topNode->next;
      delete node;
      --count;
      return item;
   }

   Stack& operator=(Stack&& other) noexcept { // operator overload
      if (this != &other) {
         while (!isEmpty()) {
            pop();
         }

         topNode = other.topNode;
         count = other.count;

         other.topNode = nullptr;
         other.count = 0;
      }
      return *this;
   }

   [[nodiscard]] const T &top() const {
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

#endif// STACK_H