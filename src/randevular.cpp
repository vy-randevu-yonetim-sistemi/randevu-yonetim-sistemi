#include "randevular.h"
#include "ui_randevular.h"
#include "sqlite.h"
#include "randevu.h"

#include <QMessageBox>
#include <QDate>

randevular::randevular(QMainWindow *mainWindow, QWidget *parent)
        : QMainWindow(parent), m_mainWindow(mainWindow) {
   ui = new Ui::randevular;
   ui->setupUi(this);

   connect(ui->btnAnaSayfa, &QPushButton::clicked, this, &randevular::randevuGoster);
   connect(ui->pushButton_3, &QPushButton::clicked, this, &randevular::geriSayfaGec);
   //connect(ui->comboBoxDoktor, &QComboBox::currentTextChanged, this, &randevular::hastaListele);
   connect(ui->btnUstSonraki, &QPushButton::clicked, this, &randevular::sonrakiRandevu);
   // connect(ui->btnUstOnceki, &QPushButton::clicked, this, randevular::oncekiRandevu); fonksiyonlar eklenmiş ama boş, hata veriyor
   connect(ui->btnAltSonraki, &QPushButton::clicked, this, &randevular::sonrakiIslem);
   // connect(ui->btnAltOnceki, &QPushButton::clicked, this, randevular::oncekiIslem()); // fonksiyonlar eklenmiş ama boş, hata veriyor
}

randevular::~randevular() {
   delete ui;
}

void randevular::oncekiRandevu(){

}

void randevular::sonrakiIslem(){

}

void randevular::oncekiIslem(){

}

void randevular::geriSayfaGec() {
   this->hide();
   if (m_mainWindow) m_mainWindow->show();
}

void randevular::sonrakiRandevu() {
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

void randevular::randevuGoster() {
   ui->tableWidget->setRowCount(0);

   QString doktorAdi = ui->comboBoxDoktor->currentText().trimmed();
   if (doktorAdi.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen bir doktor seçin.");
      return;
   }

   QList<Randevu> filtered;
   const auto &list = SQLiteManager::instance().randevuListesi();

   list.traverse([&](const Randevu &r) {
      if (r.doktor == doktorAdi) {
         filtered.append(r);
      }
   });

   std::sort(filtered.begin(), filtered.end(), [](const Randevu &a, const Randevu &b) {
      QDate dateA = QDate::fromString(a.tarih, Qt::ISODate);
      QDate dateB = QDate::fromString(b.tarih, Qt::ISODate);

      if (dateA == dateB) {
         QTime timeA = QTime::fromString(a.saat, "HH:mm");
         QTime timeB = QTime::fromString(b.saat, "HH:mm");
         return timeA < timeB;
      }

      return dateA < dateB;
   });

   for (int i = 0; i < filtered.size(); ++i) {
      const Randevu &r = filtered[i];

      ui->tableWidget->insertRow(i);
      ui->tableWidget->setItem(i, 0, new QTableWidgetItem(r.doktor));
      ui->tableWidget->setItem(i, 1, new QTableWidgetItem(r.ad));
      ui->tableWidget->setItem(i, 2, new QTableWidgetItem(r.saat));
      ui->tableWidget->setItem(i, 3, new QTableWidgetItem(r.tarih));
   }
}

/*
void randevular::hastaListele(const QString &doktorAdi) {
   QList<Randevu> hastalar = SQLiteManager::instance().doktorRandevular(doktorAdi);

   ui->textEdit->clear();
   for (const Randevu &r: hastalar) {
      ui->textEdit->append(r.ad + " - " + r.tc + " - " + r.tarih + " " + r.saat + " " + r.doktor);
   }
}
*/
