#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlite.h"
#include "randevu.h"

#include <QMessageBox>
#include <QStringListModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
   ui->setupUi(this);

   connect(ui->btnEkle, &QPushButton::clicked, this, &MainWindow::randevuEkle);
   connect(ui->btnSil, &QPushButton::clicked, this, &MainWindow::randevuSil);
   connect(ui->btnGoster, &QPushButton::clicked, this, &MainWindow::randevuGoster);
   connect(ui->btnSorgu, &QPushButton::clicked, this, &MainWindow::randevuSorgula);
   connect(ui->btnStackEkle, &QPushButton::clicked, this, &MainWindow::stackEkle);
   connect(ui->btnStackCikar, &QPushButton::clicked, this, &MainWindow::stacktenCikar);
   connect(ui->btnStackGoster, &QPushButton::clicked, this, &MainWindow::stackGoster);
   
   if (!SQLiteManager::instance().openDatabase()) {
      QMessageBox::critical(this, "Veritabanı Hatası", "Veritabanı açılamadı!");
   }
}

MainWindow::~MainWindow() {
   delete ui;
}

void MainWindow::randevuEkle() {
   Randevu r;
   r.ad = ui->lineEditAd->text().trimmed();
   r.tc = ui->lineEditTC->text().trimmed();
   r.tarih = ui->lineEditTarih->text().trimmed();
   r.saat = ui->comboBoxSaat->currentText();
   r.doktor = ui->comboBoxDoktor->currentText();

   if (r.ad.isEmpty() || r.tc.isEmpty() || r.tarih.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen tüm alanları doldurun.");
      return;
   }

   if (SQLiteManager::instance().randevuEkle(r)) {
      ui->textEditListe->append("✓ Veritabanına eklendi:\nHasta Adı: " + r.ad);
      bekleyenRandevular.enqueue(r);
   } else {
      ui->textEditListe->append("× Kayıt başarısız.");
   }

   ui->lineEditAd->clear();
   ui->lineEditTC->clear();
   ui->lineEditTarih->clear();
}

void MainWindow::sonrakiRandevu() {
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
      QString line = QString("%1 - %2 - %3 - %4 - %5")
              .arg(r.ad, r.tc, r.tarih, r.saat, r.doktor);
      randevuListe.append(line);
   }

   auto *model = new QStringListModel(randevuListe, this);
   ui->listViewListe->setModel(model);
}

void MainWindow::randevuSorgula() {
   QString tc = ui->lineEditTC->text().trimmed();
   if (tc.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen TC numarasını girin.");
      return;
   }

   QList<Randevu> randevular = SQLiteManager::instance().randevuTC(tc);

   QStringList randevuListe;
   if (randevular.isEmpty()) {
      randevuListe.append("Bu TC numarasına ait randevu bulunmamaktadır.");
   } else {
      for (const Randevu &r: randevular) {
         QString line = QString("Hasta Adı: %1\nTC No: %2\nTarih: %3\nSaat: %4\nDoktor: %5\n-----------")
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
   r.tarih = bilgiler[2];
   r.saat = bilgiler[3];
   r.doktor = bilgiler[4];

   if (SQLiteManager::instance().randevuSil(r)) {
      QMessageBox::information(this, "Başarılı", "Seçilen randevu silindi.");
      randevuGoster();
   } else {
      QMessageBox::warning(this, "Hata", "Silme işlemi başarısız.");
   }

void MainWindow::stackEkle() {
   Randevu r;
   r.ad = ui->lineEditAd->text().trimmed();
   r.tc = ui->lineEditTC->text().trimmed();
   r.tarih = ui->lineEditTarih->text().trimmed();
   r.saat = ui->comboBoxSaat->currentText();
   r.doktor = ui->comboBoxDoktor->currentText();
  
   if (r.ad.isEmpty() || r.tc.isEmpty() || r.tarih.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Stack'e eklemek için zorunlu alanları doldurun.");
      return;
   }
  
   randevuStack.push(r);
   ui->textEditListe->append("✓ Stack'e eklendi: " + r.ad);
  }

  void MainWindow::stacktenCikar() {
   try {
       Randevu r = randevuStack.pop();
       ui->textEditListe->append("✗ Stack'ten çıkarıldı: " + r.ad);
   } catch (const std::runtime_error& e) {
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
   } catch (const std::runtime_error& e) {
       QMessageBox::warning(this, "Stack Hatası", e.what());
   }
}

}