#ifndef VERIYAPILARI_QUEUE_H
#define VERIYAPILARI_QUEUE_H

#include <stdexcept>

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

public:
   Queue() = default;

   ~Queue() {
      clear();
   }

   Queue(const Queue&) = delete;
   Queue& operator=(const Queue&) = delete;

   void enqueue(const T& item) {
      Node* node = new Node(item);
      if (rearNode)
         rearNode->next = node;
      else
         frontNode = node;
      rearNode = node;
   }

   T dequeue() {
      if (isEmpty())
         throw std::runtime_error("Queue is empty");

      Node* node = frontNode;
      T item = node->data;
      frontNode = frontNode->next;
      if (!frontNode) rearNode = nullptr;
      delete node;
      return item;
   }

   const T& front() const {
      if (isEmpty())
         throw std::runtime_error("Queue is empty");
      return frontNode->data;
   }

   [[nodiscard]] bool isEmpty() const {
      return frontNode == nullptr;
   }

   void clear() {
      while (!isEmpty()) {
         dequeue();
      }
   }
};

#endif // VERIYAPILARI_QUEUE_H

