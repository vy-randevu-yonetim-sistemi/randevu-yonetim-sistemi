#ifndef VERIYAPILARI_RANDEVU_H
#define VERIYAPILARI_RANDEVU_H
#pragma once
#include <QString>
#include "randevu.h"
#include <QMainWindow>
struct Randevu {
    QString ad;
    QString tc;
    QString tarih;
    QString saat;
    QString doktor;

    bool operator<(const Randevu& other) const {
       if (tarih == other.tarih)
          return saat < other.saat;
       return tarih < other.tarih;
    }
};

#endif // VERIYAPILARI_RANDEVU_H
