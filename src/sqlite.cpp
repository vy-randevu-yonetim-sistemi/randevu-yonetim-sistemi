#include "sqlite.h"
#include "randevu.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

SQLiteManager::SQLiteManager()
    : connectionName("RandevuDBConnection") {}

SQLiteManager::~SQLiteManager() {
   QSqlDatabase db = QSqlDatabase::database(connectionName, false);
   if (db.isOpen()) {
      db.close();
   }
   QSqlDatabase::removeDatabase(connectionName);
}

SQLiteManager &SQLiteManager::instance() {
   static SQLiteManager _instance;
   return _instance;
}

bool SQLiteManager::openDatabase(const QString &path) {
   if (QSqlDatabase::contains(connectionName)) {
      return true;
   }

   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
   db.setDatabaseName(path);
   dbPath = path;

   if (!db.open()) {
      qCritical() << "Failed to open database:" << db.lastError().text();
      return false;
   }

   veritabaniYukle();
   return tabloKontrol();
}

bool SQLiteManager::tabloKontrol() {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);

   const QString createSQL = R"(
        CREATE TABLE IF NOT EXISTS randevular (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ad TEXT NOT NULL,
            tc TEXT NOT NULL,
            tarih TEXT NOT NULL,
            saat TEXT NOT NULL,
            doktor TEXT NOT NULL
        )
    )";

   if (!query.exec(createSQL)) {
      qCritical() << "Failed to create table:" << query.lastError().text();
      return false;
   }

   return true;
}

bool SQLiteManager::randevuEkle(const Randevu &r) {
   randevularLL.insertSorted(r);

   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);

   query.prepare(R"(
        INSERT INTO randevular (ad, tc, tarih, saat, doktor)
        VALUES (:ad, :tc, :tarih, :saat, :doktor)
    )");

   query.bindValue(":ad", r.ad);
   query.bindValue(":tc", r.tc);
   query.bindValue(":tarih", r.tarih);
   query.bindValue(":saat", r.saat);
   query.bindValue(":doktor", r.doktor);

   if (!query.exec()) {
      qWarning() << "Ekleme işlemi başarısız oldu:" << query.lastError().text();
      return false;
   }

   return true;
}

const DoubleLinkedList<Randevu> &SQLiteManager::randevuListesi() const {
   return randevularLL;
}

QList<Randevu> SQLiteManager::randevular() const {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);
   QList<Randevu> results;

   if (!query.exec("SELECT * FROM randevular")) {
      qWarning() << "Query başarısız oldu:" << query.lastError().text();
      return results;
   }

   while (query.next()) {
      Randevu r;
      r.ad = query.value("ad").toString();
      r.tc = query.value("tc").toString();
      r.tarih = query.value("tarih").toString();
      r.saat = query.value("saat").toString();
      r.doktor = query.value("doktor").toString();
      results.append(r);
   }

   return results;
}

QList<Randevu> SQLiteManager::randevuTC(const QString &tc) const {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);
   QList<Randevu> results;

   query.prepare("SELECT * FROM randevular WHERE tc = :tc");
   query.bindValue(":tc", tc);

   if (!query.exec()) {
      qWarning() << "Select failed:" << query.lastError().text();
      return results;
   }

   while (query.next()) {
      Randevu r;
      r.ad = query.value("ad").toString();
      r.tc = query.value("tc").toString();
      r.tarih = query.value("tarih").toString();
      r.saat = query.value("saat").toString();
      r.doktor = query.value("doktor").toString();
      results.append(r);
   }

   return results;
}

bool SQLiteManager::randevuVarMi(const QString &tarih, const QString &saat, const QString &doktor) const {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);

   query.prepare(R"(
        SELECT COUNT(*) FROM randevular
        WHERE tarih = :tarih AND saat = :saat AND doktor = :doktor
    )");

   query.bindValue(":tarih", tarih);
   query.bindValue(":saat", saat);
   query.bindValue(":doktor", doktor);

   if (!query.exec()) {
      qWarning() << "Kontrol başarısız oldu:" << query.lastError().text();
      return false;
   }

   if (query.next()) {
      return query.value(0).toInt() > 0;
   }

   return false;
}

bool SQLiteManager::randevuSil(const Randevu &r) {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);

   query.prepare(R"(
        DELETE FROM randevular
        WHERE ad = :ad AND tc = :tc AND tarih = :tarih
              AND saat = :saat AND doktor = :doktor
    )");

   query.bindValue(":ad", r.ad);
   query.bindValue(":tc", r.tc);
   query.bindValue(":tarih", r.tarih);
   query.bindValue(":saat", r.saat);
   query.bindValue(":doktor", r.doktor);

   if (!query.exec()) {
      qWarning() << "Delete failed:" << query.lastError().text();
      return false;
   }

   return query.numRowsAffected() > 0;
}

void SQLiteManager::veritabaniYukle() {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);

   if (!query.exec("SELECT * FROM randevular")) {
      qWarning() << "Load failed:" << query.lastError().text();
      return;
   }

   while (query.next()) {
      Randevu r;
      r.ad = query.value("ad").toString();
      r.tc = query.value("tc").toString();
      r.tarih = query.value("tarih").toString();
      r.saat = query.value("saat").toString();
      r.doktor = query.value("doktor").toString();

      randevularLL.insertSorted(r);
   }
}

bool SQLiteManager::veritabaniSil() {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);

   if (!query.exec("DROP TABLE IF EXISTS randevular")) {
      qCritical() << "Tablo silinemedi:" << query.lastError().text();
      return false;
   }

   return tabloKontrol();
}

QStack<Randevu> SQLiteManager::stackDepola() const {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);
   QStack<Randevu> results;

   if (!query.exec("SELECT * FROM randevular")) {
      qWarning() << "Veritabanına yükleme sırasında hata oluştu:" << query.lastError().text();
      return results;
   }

   while (query.next()) {
      Randevu r;
      r.ad = query.value("ad").toString();
      r.tc = query.value("tc").toString();
      r.tarih = query.value("tarih").toString();
      r.saat = query.value("saat").toString();
      r.doktor = query.value("doktor").toString();
      results.push(r);
   }
   return results;
}

QList<Randevu> SQLiteManager::doktorRandevular(const QString &doktorAdi) const {
   QSqlDatabase db = QSqlDatabase::database(connectionName);
   QSqlQuery query(db);
   QList<Randevu> results;

   query.prepare("SELECT * FROM randevular WHERE doktor = :doktor");
   query.bindValue(":doktor", doktorAdi);

   if (!query.exec()) {
      qWarning() << "Query başarısız oldu:" << query.lastError().text();
      return results;
   }

   while (query.next()) {
      Randevu r;
      r.ad = query.value("ad").toString();
      r.tc = query.value("tc").toString();
      r.tarih = query.value("tarih").toString();
      r.saat = query.value("saat").toString();
      r.doktor = query.value("doktor").toString();
      results.append(r);
   }
   return results;
}
