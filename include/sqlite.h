#ifndef VERIYAPILARI_SQLITE_H
#define VERIYAPILARI_SQLITE_H
#pragma once

#include "randevu.h"

#include <QString>
#include <QVariantMap>
#include <QList>
#include <QStack>

class SQLiteManager {
public:
    static SQLiteManager& instance();

    bool openDatabase(const QString& path = "randevular.db");

    bool randevuEkle(const Randevu& data);
    [[nodiscard]] QList<Randevu> randevular() const;
    [[nodiscard]] QStack<Randevu> stackDepola() const;
    [[nodiscard]] QList<Randevu> randevuTC(const QString& tc) const;
    [[nodiscard]] QList<Randevu> randevularByDoktor(const QString& doktorAdi) const;
    bool randevuSil(const Randevu& data);


    SQLiteManager(const SQLiteManager&) = delete;
    SQLiteManager& operator=(const SQLiteManager&) = delete;

private:
    SQLiteManager();
    ~SQLiteManager();
   
    bool ensureTableExists();

    QString dbPath;
    QString connectionName;
};

#endif // VERIYAPILARI_SQLITE_H
