// clazy:excludeall=connect-non-signal -> Clazy strict modda olduğu için hata veriyor
// Type casting çalışmadığı için clazy'yi devre dışı bırakıyoruz

#include "mainwindow.h"
#include "hashtable.h"
#include "randevu.h"
#include "randevular.h"
#include "sqlite.h"
#include "ui_mainwindow.h"
#include "DoubleLinkedList.h"

#include <QCalendarWidget>
#include <QDebug>
#include <QMessageBox>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      randevular_form(nullptr) {
   ui->setupUi(this);
   randevular_form = new randevular(this, &doktorKuyruklari);

   connect(ui->btnEkle, &QPushButton::clicked, this, &MainWindow::randevuEkle);
   connect(ui->btnSil, &QPushButton::clicked, this, &MainWindow::randevuSil);
   //connect(ui->btnGoster, &QPushButton::clicked, this, &MainWindow::randevuGoster);
   connect(ui->btnSorgu, &QPushButton::clicked, this, &MainWindow::randevuSorgula);
   connect(ui->calendarWidgetTarih, &QCalendarWidget::selectionChanged, this, &MainWindow::tarihSec);
   connect(ui->btnRandevularSayfa, &QPushButton::clicked, this, &MainWindow::sayfaGec);
   //connect(ui->btnEkle, &QPushButton::clicked, this, &MainWindow::stackEkle);
   //connect(ui->btnSil, &QPushButton::clicked, this, &MainWindow::stacktenCikar);
   //connect(ui->btnStackGoster, &QPushButton::clicked, this, &MainWindow::stackGoster);

   ui->calendarWidgetTarih->setMinimumDate(QDate::currentDate());

   if (!SQLiteManager::instance().openDatabase()) {
      QMessageBox::critical(this, "Veritabanı Hatası", "Veritabanı açılamadı!");
   }
   randevuStack = SQLiteManager::instance().stackDepola();
}

MainWindow::~MainWindow() {
   delete ui;
}

void MainWindow::sayfaGec() {
   randevular_form->show();
   this->hide();
}

QString MainWindow::tarihSec() {
   QDate tarih = ui->calendarWidgetTarih->selectedDate();
   if (!tarih.isValid()) {
      QMessageBox::warning(this, "Hatalı Tarih", "Lütfen geçerli bir tarih seçin.");
      return {};
   }
   QString strTarih = tarih.toString(Qt::ISODate);
   return strTarih;
}

void MainWindow::randevuEkle() {
   Randevu r;
   r.ad = ui->lineEditAd->text().trimmed();
   r.tc = ui->lineEditTC->text().trimmed();
   r.tarih = tarihSec();
   r.saat = ui->comboBoxSaat->currentText();
   r.doktor = ui->comboBoxDoktor->currentText();

   if (r.ad.isEmpty() || r.tc.isEmpty() || r.tarih.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen tüm alanları doldurun.");
      return;
   }

   if (ui->lineEditTC->text().length() != 11) {
      QMessageBox::warning(this, "Hatalı Giriş", "Lütfen TC kimlik numaranızı 11 haneli olarak girin.");
      return;
   }

   for (QChar c: ui->lineEditTC->text()) {
      if (!c.isDigit()) {
         QMessageBox::warning(this, "Hatalı Giirş", "TC ifadesi sadece sayı karakterlerinden oluşmalı.");
         return;
      }
   }

   if (SQLiteManager::instance().randevuVarMi(r.tarih, r.saat, r.doktor)) {
      QMessageBox::warning(this, "Zaman Çakışması", "Bu tarih ve saatte bu doktor için zaten bir randevu var.");
      return;
   }

   if (SQLiteManager::instance().randevuEkle(r)) {
      ui->textEditListe->append("✓ Veritabanına eklendi:\nHasta Adı: " + r.ad +
                                "\nHasta TC: " + r.tc +
                                "\nRandevu Tarihi: " + r.tarih +
                                "\nRandevu Saati: " + r.saat +
                                "\nDoktor: " + r.doktor);
      bekleyenRandevular.enqueue(r);
   } else {
      ui->textEditListe->append("× Kayıt başarısız.");
   }

   ui->lineEditAd->clear();
   ui->lineEditTC->clear();
}

[[maybe_unused]] void MainWindow::sonrakiRandevu() {
   if (bekleyenRandevular.isEmpty()) {
      QMessageBox::information(this, "Bekleyen Randevu Yok", "Şu anda bekleyen randevu yok.");
      return;
   }

   Randevu r = bekleyenRandevular.dequeue();
   QString info = QString("Sıradaki Hasta:\n"
                          "Ad: %1\n"
                          "TC: %2\n"
                          "Tarih: %3\n"
                          "Saat: %4\n"
                          "Doktor: %5")
                          .arg(r.ad, r.tc, r.tarih, r.saat, r.doktor);

   QMessageBox::information(this, "Sonraki Randevu", info);
}

void MainWindow::randevuGoster() {
   ui->textEditListe->clear();

   QList<Randevu> randevular = SQLiteManager::instance().randevular();

   QStringList randevuListe;
   for (const Randevu &r: randevular) {
      if(r.tc == ui->lineEditTC->text().trimmed())
      {
      QString line = QString("%1 - %2 - %3 - %4 - %5")
                             .arg(r.ad, r.tc, r.tarih, r.saat, r.doktor);
      randevuListe.append(line);
      }
   }

   auto *model = new QStringListModel(randevuListe, this);
   ui->listViewListe->setModel(model);
}

void MainWindow::randevuSorgula() {
   HashTable tablo;
   QStringList randevuListe;

   QString tc = ui->lineEditTC->text().trimmed();
   if (tc.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen TC numarasını girin.");
      return;
   }

   QList<Randevu> randevular = SQLiteManager::instance().randevuTC(tc);

   for (const Randevu &r: randevular) {
      tablo.add(r);
   }

   QList<Randevu> sonuc = tablo.search(tc);

   if (sonuc.isEmpty()) {
      QMessageBox::warning(this, "Sonuç Bulunamadı", "Veritabanında bu TC ile ilgili randevu bulunamadı.");
      return;
   } else {
      for (const Randevu &r: sonuc) {
         QString line = QString("%1 - %2 - %3 - %4 - %5")
                                  .arg(r.ad, r.tc, r.tarih, r.saat, r.doktor);
         randevuListe.append(line);
      }
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

   QString line = selectedIndex.data(Qt::DisplayRole).toString();
   QStringList bilgiler = line.split(" - ");
   if (bilgiler.size() < 5) {
      QMessageBox::warning(this, "Hata", "Geçersiz veri formatı.");
      return;
   }

   Randevu r;
   r.ad = bilgiler[0];
   r.tc = bilgiler[1];
   QDate date = QDate::fromString(bilgiler[2], Qt::ISODate);// Adjust format as per expected input
   r.tarih = date.toString(Qt::ISODate);
   r.saat = bilgiler[3];
   r.doktor = bilgiler[4];

   if (SQLiteManager::instance().randevuSil(r)) {
      QMessageBox::information(this, "Başarılı", "Seçilen randevu silindi.");
      randevuGoster();
   } else {
      QMessageBox::warning(this, "Hata", "Silme işlemi başarısız.");
   }
}

void MainWindow::stackEkle() {
   Randevu r;
   r.ad = ui->lineEditAd->text().trimmed();
   r.tc = ui->lineEditTC->text().trimmed();
   r.tarih = tarihSec();
   r.saat = ui->comboBoxSaat->currentText();
   r.doktor = ui->comboBoxDoktor->currentText();

   if (r.ad.isEmpty() || r.tc.isEmpty() || r.tarih.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Stack'e eklemek için zorunlu alanları doldurun.");
      return;
   }

   randevuStack.push(r);
}

void MainWindow::stacktenCikar() {
   try {
      Randevu r = randevuStack.pop();
      ui->textEditListe->append("✗ Stack'ten çıkarıldı:\nHasta Adı: " + r.ad +
                                "\nHasta TC: " + r.tc +
                                "\nRandevu Tarihi: " + r.tarih +
                                "\nRandevu Saati: " + r.saat +
                                "\nDoktor: " + r.doktor);
   } catch (const std::runtime_error &e) {
      QMessageBox::warning(this, "Stack Hatası", e.what());
   }
}

void MainWindow::stackGoster() {
   try {
      Randevu r = randevuStack.top();
      QString info = QString("Stack'in En Üstündeki Randevu:\n"
                             "Ad: %1\nTC: %2\nTarih: %3\nSaat: %4\nDoktor: %5")
                             .arg(r.ad, r.tc, r.tarih, r.saat, r.doktor);
      QMessageBox::information(this, "Stack Görüntüle", info);
   } catch (const std::runtime_error &e) {
      QMessageBox::warning(this, "Stack Hatası", e.what());
   }
}

Queue<Randevu> &MainWindow::kuyrukOlustur(const QString &doktorAdi) {
   for (auto &pair : doktorKuyruklari) {
      if (pair.first == doktorAdi) {
         return pair.second;
      }
   }

   doktorKuyruklari.emplace_back(QString(doktorAdi), Queue<Randevu>());
   return doktorKuyruklari.back().second;
}