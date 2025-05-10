#ifndef VERIYAPILARI_DOUBLE_LINKED_LIST_H
#define VERIYAPILARI_DOUBLE_LINKED_LIST_H

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
          /*
           * Eğer head var ise, onun prev'ini yeni nesneye
           * atıyoruz.
           */
          head->prev = node;
       } else {
          /*
           * Eğer head yok ise, yani liste boş ise, tail'i
           * yeni nesneye atıyoruz.
           */
          tail = node;
       }
       head = node;
    }

    void addBack(const T &item) {
       Node *node = new Node(item);
       node->prev = tail;
       if (tail) {
          /*
           * Bir önceki nesne var ise, onun next'ini yeni nesneye
           * atıyoruz.
           */
          tail->next = node;
       } else {
          /*
           * Eğer tail yok ise, yani liste boş ise, head'i
           * yeni nesneye atıyoruz.
           */
          head = node;
       }
       tail = node;
    }

    T removeFront() {
       if (isEmpty()) {
          throw std::runtime_error("Liste bos");
       }
       Node *node = head;
       T item = node->data;
       head = head->next;
       if (head) {
          /*
           * Eğer head var ise, onun prev'ini nullptr yapıyoruz.
           * Böylece head'i bir sonraki nesneye atıyoruz.
           */
          head->prev = nullptr;
       } else {
          /*
           * Eğer head yok ise, yani liste boş ise, tail'i
           * nullptr yapıyoruz.
           */
          tail = nullptr;
       }
       delete node;
       return item;
    }

    T removeBack() {
       if (isEmpty()) {
          throw std::runtime_error("Liste bos");
       }
       Node *node = tail;
       T item = node->data;
       tail = tail->prev;
       if (tail) {
          /*
           * Eğer tail var ise, onun next'ini nullptr yapıyoruz.
           * Böylece tail'i bir önceki nesneye atıyoruz.
           */
          tail->next = nullptr;
       } else {
          /*
           * Eğer tail yok ise, yani liste boş ise, head'i
           * nullptr yapıyoruz.
           */
          head = nullptr;
       }
       delete node;
       return item;
    }

    T front() const {
       if (isEmpty()) {
          throw std::runtime_error("Liste bos");
       }
       /*
        * Eğer head var ise, head'in data'sını döndürüyoruz.
        * Eğer head yok ise, yani liste boş ise, hata oluşturuyoruz.
        */
       return head->data;
    }

    T back() const {
       if (isEmpty()) {
          throw std::runtime_error("Liste bos");
       }
       /*
        * Eğer tail var ise, tail'in data'sını döndürüyoruz.
        * Eğer tail yok ise, yani liste boş ise, hata oluşturuyoruz.
        */
       return tail->data;
    }

    [[nodiscard]] bool isEmpty() const {
       return head == nullptr;
    }
};

#endif // VERIYAPILARI_DOUBLE_LINKED_LIST_H
