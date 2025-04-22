#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
   ui->setupUi(this);

   connect(ui->btnEkle, &QPushButton::clicked, this, &MainWindow::randevuEkle);
   connect(ui->btnSil, &QPushButton::clicked, this, &MainWindow::randevuSil);
   connect(ui->btnGoster, &QPushButton::clicked, this, &MainWindow::randevuGoster);
   connect(ui->btnSorgu, &QPushButton::clicked, this, &MainWindow::randevuSorgula);
}

MainWindow::~MainWindow() {
   delete ui;
}

void MainWindow::randevuEkle() {
   ui->textEditListe->clear();

   QString ad = ui->lineEditAd->text();
   QString tc = ui->lineEditTC->text();
   QString tarih = ui->lineEditTarih->text();
   QString saat = ui->comboBoxSaat->currentText();
   QString doktor = ui->comboBoxDoktor->currentText();

   if (ad.isEmpty() || tc.isEmpty() || tarih.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen tüm alanları doldurun.");
      return;
   }

   QString bilgi = QString("Hasta Adı: %1\nTC No: %2\nTarih: %3\nSaat: %4\nDoktor: %5\n-----------")
                           .arg(ad, tc, tarih, saat, doktor);

   // Alanları temizle
   ui->lineEditAd->clear();
   ui->lineEditTC->clear();
   ui->lineEditTarih->clear();

   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("randevular.db");

   if (!db.open()) {
      qDebug() << "Veritabanı açılamadı:" << db.lastError().text();
   } else {
      qDebug() << "Veritabanı bağlantısı başarılı.";

      QSqlQuery query;
      query.exec("CREATE TABLE IF NOT EXISTS randevular ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "ad TEXT,"
                 "tc TEXT,"
                 "tarih TEXT,"
                 "saat TEXT,"
                 "doktor TEXT)");
   }

   QSqlQuery query;
   query.prepare("INSERT INTO randevular (ad, tc, tarih, saat, doktor) VALUES (?, ?, ?, ?, ?)");
   query.addBindValue(ad);
   query.addBindValue(tc);
   query.addBindValue(tarih);
   query.addBindValue(saat);
   query.addBindValue(doktor);

   if (!query.exec()) {
      qDebug() << "Ekleme hatası:" << query.lastError().text();
   } else {
      ui->textEditListe->append("✓ Veritabanına eklendi:\n" + bilgi);
   }
}

void MainWindow::randevuGoster() {
   ui->textEditListe->clear();

   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("randevular.db");

   QStringList randevuListe;
   QSqlQuery query;
   query.exec("SELECT * FROM randevular");

   while (query.next()) {
      QString ad = query.value("ad").toString();
      QString tc = query.value("tc").toString();
      QString tarih = query.value("tarih").toString();
      QString saat = query.value("saat").toString();
      QString doktor = query.value("doktor").toString();

      randevuListe.append(QString("%1 - %2 - %3 - %4 - %5").arg(ad, tc, tarih, saat, doktor));
   }

   auto *model = new QStringListModel(randevuListe, this);
   ui->listViewListe->setModel(model);
}

void MainWindow::randevuSorgula() {
   QString tc = ui->lineEditTC->text();

   if (tc.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen TC numarasını girin.");
      return;
   }

   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("randevular.db");

   if (!db.open()) {
      qDebug() << "Veritabanı açılamadı:" << db.lastError().text();
      return;
   }

   QSqlQuery query;
   query.prepare("SELECT * FROM randevular WHERE tc = ?");
   query.addBindValue(tc);

   ui->textEditListe->clear();
   QStringList randevuListe;

   if (query.next()) {
      // Veritabanında TC numarasına ait randevu bulundu
      do {
         QString ad = query.value("ad").toString();
         QString tarih = query.value("tarih").toString();
         QString saat = query.value("saat").toString();
         QString doktor = query.value(doktor).toString();

         randevuListe.append(QString("Hasta Adı: %1\nTC No: %2\nTarih: %3\n Saat: %4\n Doktor: %5\n-----------")
                                     .arg(ad, tc, tarih, saat, doktor));

      } while (query.next());
   } else {
      randevuListe.append("Bu TC numarasına ait randevu bulunmamaktadır.");
   }

   auto *model = new QStringListModel(randevuListe, this);
   ui->listViewListe->setModel(model);
}

void MainWindow::randevuSil() {
   QModelIndex selectedIndex = ui->listViewListe->currentIndex();

   if (!selectedIndex.isValid()) {
      QMessageBox::warning(this, "Hata", "Lütfen silmek için bir randevu seçin.");
      return;
   }

   QString secilenSatir = selectedIndex.data(Qt::DisplayRole).toString();
   QStringList bilgiler = secilenSatir.split(" - ");

   QString ad = bilgiler[0];
   QString tc = bilgiler[1];
   QString tarih = bilgiler[2];
   QString saat = bilgiler[3];
   QString doktor = bilgiler[4];

   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("randevular.db");

   if (!db.open()) {
      qDebug() << "Veritabanı açılamadı:" << db.lastError().text();
      return;
   }

   QSqlQuery query;
   query.prepare(
           "DELETE FROM randevular WHERE ad = ? AND tc = ? AND tarih = ? AND saat = ? AND doktor = ?");// Bu kısmı id değerine göre silecek şekilde ayarla.
   query.addBindValue(ad);
   query.addBindValue(tc);
   query.addBindValue(tarih);
   query.addBindValue(saat);
   query.addBindValue(doktor);

   if (!query.exec()) {
      qDebug() << "Silme hatası:" << query.lastError().text();
   } else {
      QMessageBox::information(this, "Sidin işte", "Seçilen randevu silindi.");
   }
}
