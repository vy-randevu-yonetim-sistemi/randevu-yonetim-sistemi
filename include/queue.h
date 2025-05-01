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

    Node* frontNode;
    Node* rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    ~Queue() {
       while (!isEmpty()) {
          dequeue();
       }
    }

    void enqueue(const T& item) {
       Node* node = new Node(item);
       if (rearNode)
          rearNode->next = node;
       else
          frontNode = node;
       rearNode = node;
    }

    T dequeue() {
       if (isEmpty()) {
          throw std::runtime_error("Queue is empty");
       } else {
          Node* node = frontNode;
          T item = node->data;
          frontNode = frontNode->next;
          if (!frontNode) rearNode = nullptr;
          delete node;
          return item;
       }
    }

    T front() const {
       if (isEmpty()) {
          throw std::runtime_error("Queue is empty");
       } else {
          return frontNode->data;
       }
    }

    bool isEmpty() const {
       return frontNode == nullptr;
    }
};

#endif // VERIYAPILARI_QUEUE_H