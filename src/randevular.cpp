// clazy:excludeall=connect-non-signal -> Clazy strict modda olduğu için hata veriyor
// Type casting çalışmadığı için clazy'yi devre dışı bırakıyoruz
#include "randevular.h"
#include "randevu.h"
#include "sqlite.h"
#include "ui_randevular.h"

#include <QDate>
#include <QMessageBox>

randevular::randevular(QMainWindow *mainWindow, std::vector<std::pair<QString, Queue<Randevu>>> *kuyruklar, QWidget *parent)
    : QMainWindow(parent), m_mainWindow(mainWindow), doktorKuyruklari(kuyruklar) {
   ui = new Ui::randevular;
   ui->setupUi(this);

   connect(ui->btnAnaSayfa, &QPushButton::clicked, this, &randevular::randevuGoster);
   connect(ui->pushButton_3, &QPushButton::clicked, this, &randevular::geriSayfaGec);
   connect(ui->comboBoxDoktor, &QComboBox::currentTextChanged, this, &randevular::hastaListele);
   connect(ui->btnUstSonraki, &QPushButton::clicked, this, &randevular::sonrakiRandevu);
   // connect(ui->btnUstOnceki, &QPushButton::clicked, this, randevular::oncekiRandevu); //fonksiyonlar eklenmiş ama boş, hata veriyor
   connect(ui->btnAltSonraki, &QPushButton::clicked, this, &randevular::sonrakiIslem);
   //connect(ui->btnAltOnceki, &QPushButton::clicked, this, randevular::oncekiIslem()); // fonksiyonlar eklenmiş ama boş, hata veriyor
}

randevular::~randevular() {
   delete ui;
}


void randevular::oncekiRandevu() {
   if (!guncelHastaListesi.isEmpty() && guncelHastaIndex > 0) {
      guncelHastaIndex--;
      hastaBilgileriniGoster();
   }
}

void randevular::sonrakiIslem() {
}

void randevular::oncekiIslem() {
}

void randevular::geriSayfaGec() {
   this->hide();
   if (m_mainWindow) m_mainWindow->show();
}

void randevular::sonrakiRandevu() {
   qDebug () << "Sonraki randevu butonuna tıklandı";
   if (!guncelHastaListesi.isEmpty() && guncelHastaIndex < guncelHastaListesi.size() - 1) {
      guncelHastaIndex++;
      hastaBilgileriniGoster();
   }
}

void randevular::randevuGoster() {
   ui->tableWidget->setRowCount(0);
   guncelHastaListesi.clear();
   guncelHastaIndex = -1;
   ui->textEdit->clear();// Sağdaki detay alanlarını temizle
   ui->textEdit_2->clear();

   QString doktorAdi = ui->comboBoxDoktor->currentText().trimmed();
   if (doktorAdi.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen bir doktor seçin.");
      return;
   }

   const auto &list = SQLiteManager::instance().randevuListesi();

   list.traverse([&](const Randevu &r) {
      if (r.doktor == doktorAdi) {
         guncelHastaListesi.append(r);
      }
   });

   std::sort(guncelHastaListesi.begin(), guncelHastaListesi.end(), [](const Randevu &a, const Randevu &b) {
      QDate dateA = QDate::fromString(a.tarih, Qt::ISODate);
      QDate dateB = QDate::fromString(b.tarih, Qt::ISODate);

      if (dateA == dateB) {
         QTime timeA = QTime::fromString(a.saat, "HH:mm");
         QTime timeB = QTime::fromString(b.saat, "HH:mm");
         return timeA < timeB;
      }
      return dateA < dateB;
   });

   for (int i = 0; i < guncelHastaListesi.size(); ++i) {
      const Randevu &r = guncelHastaListesi[i];
      ui->tableWidget->insertRow(i);
      ui->tableWidget->setItem(i, 0, new QTableWidgetItem(r.doktor));
      ui->tableWidget->setItem(i, 1, new QTableWidgetItem(r.ad));
      ui->tableWidget->setItem(i, 2, new QTableWidgetItem(r.saat));
      ui->tableWidget->setItem(i, 3, new QTableWidgetItem(r.tarih));
   }

   // İlk hastanın detaylarını göster eğer liste doluysa
   if (!guncelHastaListesi.isEmpty()) {
      guncelHastaIndex = 0;
      hastaBilgileriniGoster();
   }
}
void randevular::hastaBilgileriniGoster() {
   if (guncelHastaIndex >= 0 && guncelHastaIndex < guncelHastaListesi.size()) {
      const Randevu &hasta = guncelHastaListesi[guncelHastaIndex];
      QString detaylar = QString("Ad: %1\nTC: %2\nTarih: %3\nSaat: %4\nDoktor: %5")
                                 .arg(hasta.ad, hasta.tc, hasta.tarih, hasta.saat, hasta.doktor);
      ui->textEdit->setText(detaylar);// Veya ui->textEdit_2->setText(detaylar); hangi alanı kullanmak isterseniz
   } else {
      ui->textEdit->clear();
      ui->textEdit_2->clear();
   }
}


void randevular::hastaListele(const QString &doktorAdi) {
   QList<Randevu> hastalar = SQLiteManager::instance().doktorRandevular(doktorAdi);

   ui->textEdit->clear();
   for (const Randevu &r: hastalar) {
      ui->textEdit->append(r.ad + " - " + r.tc + " - " + r.tarih + " " + r.saat + " " + r.doktor);
   }
}
