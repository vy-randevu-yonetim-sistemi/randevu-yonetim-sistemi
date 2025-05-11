#include "stack.h"

Stack::~Stack() {
   while (!isEmpty()) {
      pop();
   }
}

void Stack::push(const Randevu &item) {
   Node *node = new Node(item);
   node->next = topNode;
   topNode = node;
   ++count;
}

Randevu Stack::pop() {
   if (isEmpty())
      throw std::runtime_error("Stack is empty");

   Node *node = topNode;
   Randevu item = node->data;
   topNode = topNode->next;
   delete node;
   --count;
   return item;
}

const Randevu &Stack::top() const {
   if (isEmpty())
      throw std::runtime_error("Stack is empty");

   return topNode->data;
}

bool Stack::isEmpty() const {
   return topNode == nullptr;
}

size_t Stack::size() const {
   return count;
}