#include "stack.h"

Stack::~Stack() {
   while (!isEmpty()) {
      pop();
   }
}

void Stack::push(const Randevu &item) {
   Node *newNode = new Node(item);
   newNode->next = topNode;
   topNode = newNode;
}

Randevu Stack::pop() {
   if (isEmpty()) {
      throw std::runtime_error("Stack boş: pop() işlemi yapılamaz!");
   }
   Node *temp = topNode;
   Randevu poppedData = temp->data;
   topNode = topNode->next;
   delete temp;
   return poppedData;
}

Randevu Stack::top() const {
   if (isEmpty()) {
      throw std::runtime_error("Stack boş: top() işlemi yapılamaz!");
   }
   return topNode->data;
}

bool Stack::isEmpty() const {
   return topNode == nullptr;
}

size_t Stack::size() const {
   size_t count = 0;
   Node *current = topNode;
   while (current != nullptr) {
      count++;
      current = current->next;
   }
   return count;
}