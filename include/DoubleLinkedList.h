#ifndef VERIYAPILARI_DOUBLE_LINKED_LIST_H
#define VERIYAPILARI_DOUBLE_LINKED_LIST_H

#include <functional>
#include <stdexcept>

template<typename T>
class DoubleLinkedList {
private:
   struct Node {
      T data;
      Node *prev;
      Node *next;

      explicit Node(const T &d) : data(d), prev(nullptr), next(nullptr) {}
   };

   Node *head;
   Node *tail;

public:
   DoubleLinkedList() : head(nullptr), tail(nullptr) {}

   ~DoubleLinkedList() {
      while (!isEmpty()) {
         removeFront();
      }
   }

   void addFront(const T &item) {
      Node *node = new Node(item);
      node->next = head;
      if (head) {
         head->prev = node;
      } else {
         tail = node;
      }
      head = node;
   }

   void addBack(const T &item) {
      Node *node = new Node(item);
      node->prev = tail;
      if (tail) {
         tail->next = node;
      } else {
         head = node;
      }
      tail = node;
   }

   T removeFront() {
      if (isEmpty()) {
         throw std::runtime_error("List is empty");
      }

      Node *node = head;
      T item = node->data;
      head = head->next;

      if (head) {
         head->prev = nullptr;
      } else {
         tail = nullptr;
      }

      delete node;
      return item;
   }

   T removeBack() {
      if (isEmpty()) {
         throw std::runtime_error("List is empty");
      }

      Node *node = tail;
      T item = node->data;
      tail = tail->prev;

      if (tail) {
         tail->next = nullptr;
      } else {
         head = nullptr;
      }

      delete node;
      return item;
   }

   T front() const {
      if (isEmpty()) {
         throw std::runtime_error("List is empty");
      }
      return head->data;
   }

   T back() const {
      if (isEmpty()) {
         throw std::runtime_error("List is empty");
      }
      return tail->data;
   }

   void traverse(const std::function<void(const T &)> &func) const {
      Node *current = head;
      while (current) {
         func(current->data);
         current = current->next;
      }
   }

   void insertSorted(const T &item) {
      Node *newNode = new Node(item);

      if (!head) {
         head = tail = newNode;
         return;
      }

      Node *current = head;
      while (current) {
         if (item < current->data) {
            newNode->next = current;
            newNode->prev = current->prev;

            if (current->prev) {
               current->prev->next = newNode;
            } else {
               head = newNode;
            }

            current->prev = newNode;
            return;
         }
         current = current->next;
      }

      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
   }

   [[nodiscard]] bool isEmpty() const {
      return head == nullptr;
   }
};

#endif// VERIYAPILARI_DOUBLE_LINKED_LIST_H