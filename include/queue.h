#ifndef VERIYAPILARI_QUEUE_H
#define VERIYAPILARI_QUEUE_H

#include <stdexcept>
#include <utility>

template<typename T>
class Queue {
private:
   struct Node {
      T data;
      Node* next;

      explicit Node(const T& d) : data(d), next(nullptr) {}
   };

   Node* frontNode = nullptr;
   Node* rearNode = nullptr;
   size_t count = 0;

public:
   Queue() = default;

   ~Queue() {
      clear();
   }

   Queue(const Queue&) = delete;
   Queue& operator=(const Queue&) = delete;

   Queue(Queue&& other) noexcept {
      frontNode = other.frontNode;
      rearNode = other.rearNode;
      count = other.count;

      other.frontNode = nullptr;
      other.rearNode = nullptr;
      other.count = 0;
   }

   Queue& operator=(Queue&& other) noexcept {
      if (this != &other) {
         clear();

         frontNode = other.frontNode;
         rearNode = other.rearNode;
         count = other.count;

         other.frontNode = nullptr;
         other.rearNode = nullptr;
         other.count = 0;
      }
      return *this;
   }

   void enqueue(const T& item) {
      Node* node = new Node(item);
      if (rearNode) {
         rearNode->next = node;
      } else {
         frontNode = node;
      }
      rearNode = node;
      ++count;
   }

   T dequeue() {
      if (isEmpty()) {
         throw std::runtime_error("Queue boş");
      }

      Node* node = frontNode;
      T item = node->data;
      frontNode = frontNode->next;
      if (!frontNode) {
         rearNode = nullptr;
      }
      delete node;
      --count;
      return item;
   }

   [[nodiscard]] const T& front() const {
      if (isEmpty()) {
         throw std::runtime_error("Queue boş");
      }
      return frontNode->data;
   }

   [[nodiscard]] const T& peek() const {
      return front();
   }

   [[nodiscard]] bool isEmpty() const {
      return frontNode == nullptr;
   }

   [[nodiscard]] size_t size() const {
      return count;
   }

   void clear() {
      while (!isEmpty()) {
         dequeue();
      }
   }
};

#endif // VERIYAPILARI_QUEUE_H