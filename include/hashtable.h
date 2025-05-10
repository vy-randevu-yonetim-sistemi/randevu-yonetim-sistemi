#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdexcept>
#include "randevu.h"
#include <QString>
#include <QList>
#include <QChar>
#include <utility>

        class HashTable {

private:
   struct Node {
      QString tc;
      QList<Randevu> randevuListesi;
      Node* next;
      explicit Node(QString  tc) : tc(std::move(tc)), next(nullptr) {}
   };
   QList<Node*> table;
   int size;

public:
   HashTable() : size(7919), table(7919, nullptr) {}
   ~HashTable(){
      for (auto node : table) {
         while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
         }
      }
   }

   [[nodiscard]] int hashFunction(const QString& tc)const {
      int hash = 0;
      for(const QChar& ch : tc)
      {
         hash = (hash * 104729 + ch.unicode()) % size;
      }
      return hash;
   }

   void add(const Randevu& r){
      int index = hashFunction(r.tc);
      if(!table[index]){
         table[index] = new Node(r.tc);
      }

      if (table[index]->tc == r.tc) {
         table[index]->randevuListesi.append(r);
         return;
      }
   }

   [[nodiscard]] QList<Randevu> search(const QString& tc) const {
      int index = hashFunction(tc);
      if (!table[index] || table[index]->tc != tc) {
         return {};
      }
      else if (table[index]->randevuListesi.isEmpty()) {
         throw std::runtime_error("Hash Table is empty");
      }

      QList<Randevu> result;

      while (!table[index]->randevuListesi.isEmpty()) {
         result.append(table[index]->randevuListesi.takeFirst());
      }
      return result;
   }
};
#endif// HASHTABLE_H
