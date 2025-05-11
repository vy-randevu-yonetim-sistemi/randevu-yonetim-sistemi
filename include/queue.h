#ifndef VERIYAPILARI_QUEUE_H
#define VERIYAPILARI_QUEUE_H

#include <stdexcept>

template<typename T>
class Queue {
private:
   struct Node {
      T data;
      Node *next;

      explicit Node(const T &d) : data(d), next(nullptr) {}
   };

   Node *frontNode = nullptr;
   Node *rearNode = nullptr;
   size_t count = 0;

public:
   Queue() = default;
   ~Queue() { clear(); }

   // Disable copy operations
   Queue(const Queue &) = delete;
   Queue &operator=(const Queue &) = delete;

   // Enable move operations
   Queue(Queue &&) noexcept = default;
   Queue &operator=(Queue &&) noexcept = default;

   void enqueue(const T &item) {
      Node *node = new Node(item);
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
         throw std::runtime_error("Queue is empty");
      }

      Node *node = frontNode;
      T item = node->data;
      frontNode = frontNode->next;

      if (!frontNode) {
         rearNode = nullptr;
      }

      delete node;
      --count;
      return item;
   }

   const T &front() const {
      if (isEmpty()) {
         throw std::runtime_error("Queue is empty");
      }
      return frontNode->data;
   }

   const T &peek() const { return front(); }

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

#endif// VERIYAPILARI_QUEUE_H