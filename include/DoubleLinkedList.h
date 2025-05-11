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

   [[maybe_unused]] void addFront(const T &item) {
      Node *node = new Node(item);
      node->next = head;
      if (head) {
         head->prev = node;
      } else {
         tail = node;
      }
      head = node;
   }

   [[maybe_unused]] void addBack(const T &item) {
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

   [[maybe_unused]] T removeBack() {
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

   [[maybe_unused]] T front() const {
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

   void insertSorted(const T& item) {
      Node* newNode = new Node(item);

      if (!head) {
         head = tail = newNode;
         return;
      }

      Node* current = head;
      while (current && !(item < current->data)) {
         current = current->next;
      }

      if (!current) {
         tail->next = newNode;
         newNode->prev = tail;
         tail = newNode;
         return;
      }

      newNode->next = current;
      newNode->prev = current->prev;

      if (current->prev) {
         current->prev->next = newNode;
      } else {
         head = newNode;
      }

      current->prev = newNode;
   }

   bool removeFirstMatch(const T& item) {
      Node* current = head;

      while (current) {
         if (current->data == item) {
            if (current->prev) {
               current->prev->next = current->next;
            } else {
               head = current->next;
            }

            if (current->next) {
               current->next->prev = current->prev;
            } else {
               tail = current->prev;
            }

            delete current;
            return true;
         }
         current = current->next;
      }

      return false; // Item not found
   }

   [[nodiscard]] bool isEmpty() const {
      return head == nullptr;
   }
};

#endif// VERIYAPILARI_DOUBLE_LINKED_LIST_H