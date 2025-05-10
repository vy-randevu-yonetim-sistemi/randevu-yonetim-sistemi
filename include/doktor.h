#ifndef DOKTOR_H
#define DOKTOR_H

#include <QString>

class Doktor {
public:
   QString ad;
   QString uzmanlik;

   Doktor() {}
   Doktor(const QString& ad, const QString& uzmanlik);
   DoubleLinkedList<Doktor>::Node* aktifDoktor = nullptr;


};

#endif // DOKTOR_H
