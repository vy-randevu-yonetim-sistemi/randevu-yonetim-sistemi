#ifndef VERIYAPILARI_SQLITE_H
#define VERIYAPILARI_SQLITE_H

#include "DoubleLinkedList.h"
#include "appointment.h"

#include <QList>
#include <QStack>
#include <QString>
#include <QVariantMap>

class SQLiteManager {
public:
   static SQLiteManager &instance();

   bool openDatabase(const QString &path = "randevular.db");

   bool randevuEkle(const Randevu &data);
   bool randevuSil(const Randevu &data);

   void veritabaniYukle();

   [[nodiscard]] QList<Randevu> randevular() const;
   [[nodiscard]] QList<Randevu> randevuTC(const QString &tc) const;
   [[nodiscard]] QList<Randevu> doktorRandevular(const QString &doktorAdi) const;
   [[nodiscard]] QStack<Randevu> stackDepola() const;
   [[nodiscard]] const DoubleLinkedList<Randevu> &randevuListesi() const;
   [[nodiscard]] bool randevuVarMi(const QString &tarih, const QString &saat, const QString &doktor) const;

   SQLiteManager(const SQLiteManager &) = delete;
   SQLiteManager &operator=(const SQLiteManager &) = delete;

private:
   SQLiteManager();
   ~SQLiteManager();

   bool tabloKontrol();

   DoubleLinkedList<Randevu> randevularLL;
   QString dbPath;
   QString connectionName;
};

#endif// VERIYAPILARI_SQLITE_H