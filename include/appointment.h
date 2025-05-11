#ifndef VERIYAPILARI_APPOINTMENT_H
#define VERIYAPILARI_APPOINTMENT_H

#include <QString>

struct Randevu {
   QString ad;
   QString tc;
   QString tarih;
   QString saat;
   QString doktor;

   bool operator<(const Randevu &other) const {
      if (tarih == other.tarih)
         return saat < other.saat;
      return tarih < other.tarih;
   }

   bool operator==(const Randevu& other) const {
      return tc == other.tc &&
             tarih == other.tarih &&
             saat == other.saat;
   }
};

#endif// VERIYAPILARI_APPOINTMENT_H