#ifndef VERIYAPILARI_DOKTOR_H
#define VERIYAPILARI_DOKTOR_H

#pragma once

#include "DoubleLinkedList.h"
#include <QString>

class Doktor {
public:
    QString ad;
    QString uzmanlik;

    Doktor() = default;
    Doktor(const QString& ad, const QString& uzmanlik)
            : ad(ad), uzmanlik(uzmanlik) {}

    DoubleLinkedList<Doktor>::Node* aktifDoktor = nullptr;
};

#endif // VERIYAPILARI_DOKTOR_H