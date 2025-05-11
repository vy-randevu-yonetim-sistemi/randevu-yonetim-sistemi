#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "appointment.h"

#include <stdexcept>
#include <utility>

#include <QChar>
#include <QList>
#include <QString>

class HashTable {
private:
   struct Node {
      QString tc;
      QList<Randevu> randevuListesi;
      Node *next;

      explicit Node(QString tc) : tc(std::move(tc)), next(nullptr) {}
   };

   QList<Node *> table;
   int size;

public:
   HashTable() : size(7919), table(7919, nullptr) {}

   ~HashTable() {
      for (auto &node: table) {
         while (node) {
            Node *temp = node;
            node = node->next;
            delete temp;
         }
      }
   }

   [[nodiscard]] int hashFunction(const QString &tc) const {
      int hash = 0;
      for (const QChar &ch: tc) {
         hash = (hash * 104729 + ch.unicode()) % size;
      }
      return hash;
   }

   void add(const Randevu &r) {
      int index = hashFunction(r.tc);
      Node *current = table[index];

      while (current) {
         if (current->tc == r.tc) {
            current->randevuListesi.append(r);
            return;
         }
         current = current->next;
      }

      Node *newNode = new Node(r.tc);
      newNode->randevuListesi.append(r);
      newNode->next = table[index];
      table[index] = newNode;
   }

   [[nodiscard]] QList<Randevu> search(const QString &tc) const {
      int index = hashFunction(tc);
      Node *current = table[index];

      while (current) {
         if (current->tc == tc) {
            return current->randevuListesi;
         }
         current = current->next;
      }

      return {};
   }
};

#endif// HASHTABLE_H