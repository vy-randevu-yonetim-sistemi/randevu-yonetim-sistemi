// clazy:excludeall=connect-non-signal -> Clazy strict modda olduğu için hata veriyor
// Type casting çalışmadığı için clazy'yi devre dışı bırakıyoruz
#include "randevular.h"
#include "appointment.h"
#include "sqlite.h"
#include "ui_randevular.h"

#include <algorithm>

#include <QDate>
#include <QMessageBox>

randevular::randevular(QMainWindow *mainWindow, std::vector<std::pair<QString, Queue<Randevu>>> *kuyruklar, QWidget *parent)
    : QMainWindow(parent), m_mainWindow(mainWindow), doktorKuyruklari(kuyruklar), aktifDoktor("") {
   if (!doktorKuyruklari) {
      doktorKuyruklari = new std::vector<std::pair<QString, Queue<Randevu>>>();
   }
   ui = new Ui::randevular;
   ui->setupUi(this);

   connect(ui->btnAnaSayfa, &QPushButton::clicked, this, &randevular::randevuGoster);
   connect(ui->pushButton_3, &QPushButton::clicked, this, &randevular::geriSayfaGec);
   connect(ui->comboBoxDoktor, &QComboBox::currentTextChanged, this, &randevular::hastaListele);
   connect(ui->btnUstSonraki, &QPushButton::clicked, this, &randevular::sonrakiRandevu);
   connect(ui->btnLogTemizle, &QPushButton::clicked, this , &randevular::logTemizle);
}

randevular::~randevular() {
   delete ui;
}

void randevular::logTemizle(){
   ui->textEdit_2->clear();
   while(!islenenRandevular.isEmpty()){
      islenenRandevular.pop();
   }
}

void randevular::doktorDegisti(const QString &yeniDoktor) {
   if (aktifDoktor != yeniDoktor) {
      while (!islenenRandevular.isEmpty()) {
         islenenRandevular.pop();
      }
      ui->textEdit_2->clear();
      aktifDoktor = yeniDoktor;
   }
   hastaListele(yeniDoktor);
}

void randevular::oncekiRandevu() {
   if (!guncelHastaListesi.isEmpty() && guncelHastaIndex > 0) {
      guncelHastaIndex--;
      hastaBilgileriniGoster();
   }
}

bool randevular::isAppointmentHandled(const Randevu &r) const {
   Stack<Randevu> temp = islenenRandevular;
   while (!temp.isEmpty()) {
      if (temp.pop() == r) {
         return true;
      }
   }
   return false;
}

void randevular::geriSayfaGec() {
   this->hide();
   if (m_mainWindow) m_mainWindow->show();
}

void randevular::sonrakiRandevu() {
   QString doktorAdi = ui->comboBoxDoktor->currentText().trimmed();
   if (doktorAdi.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen bir doktor seçin.");
      return;
   }

   Queue<Randevu> *queue = doktorKuyrugunuAl(doktorAdi);
   if (!queue) {
      QMessageBox::warning(this, "Hata", "Doktor kuyruğu bulunamadı.");
      return;
   }

   if (activePatient) {
      islenenRandevular.push(currentPatient);
      activePatient = false;
   }

   if (queue->isEmpty()) {
      ui->textEdit->setText("Bekleyen hasta kalmadı.");
   } else {
      currentPatient = queue->dequeue();
      activePatient = true;

      QString info = QString("Hasta:\nAd: %1\nTC: %2\nTarih: %3\nSaat: %4\nDoktor: %5").arg(currentPatient.ad, currentPatient.tc, currentPatient.tarih, currentPatient.saat, currentPatient.doktor);
      ui->textEdit->setText(info);
   }

   SQLiteManager::instance().randevuListesi().removeFront();

   if (ui->tableWidget->rowCount() > 0) {
      ui->tableWidget->removeRow(0);
   }

   ui->textEdit_2->clear();
   Stack<Randevu> temp = islenenRandevular;
   while (!temp.isEmpty()) {
      Randevu r = temp.pop();
      QString line = QString("Hasta: %1 | Doktor: %2").arg(r.ad, r.doktor);
      ui->textEdit_2->append(line);
   }
}

void randevular::randevuGoster() {
   ui->textEdit->clear();
   ui->textEdit_2->clear();
   ui->tableWidget->clearContents();
   ui->tableWidget->setRowCount(0);

   guncelHastaListesi.clear();
   guncelHastaIndex = -1;
   activePatient = false;
   currentPatient = Randevu();
   while (!islenenRandevular.isEmpty()) {
      islenenRandevular.pop();
   }

   const QString doktorAdi = ui->comboBoxDoktor->currentText().trimmed();
   if (doktorAdi.isEmpty()) {
      QMessageBox::warning(this, "Eksik Bilgi", "Lütfen bir doktor seçin.");
      return;
   }

   const auto &randevuList = SQLiteManager::instance().randevuListesi();
   randevuList.traverse([&](const Randevu &r) {
      if (r.doktor == doktorAdi)
         guncelHastaListesi.append(r);
   });

   // Sort by date and time
   std::sort(guncelHastaListesi.begin(), guncelHastaListesi.end(), [](const Randevu &a, const Randevu &b) {
      QDateTime dtA = QDateTime::fromString(a.tarih + " " + a.saat, "yyyy-MM-dd HH:mm");
      QDateTime dtB = QDateTime::fromString(b.tarih + " " + b.saat, "yyyy-MM-dd HH:mm");
      return dtA < dtB;
   });

   // Update doctor's queue
   Queue<Randevu> *queue = doktorKuyrugunuAl(doktorAdi);
   if (!queue) {
      QMessageBox::critical(this, "Hata", "Doktor kuyruğu erişilemedi.");
      return;
   }

   queue->clear();
   for (const Randevu &r : guncelHastaListesi)
      queue->enqueue(r);

   // Populate table UI
   for (int i = 0; i < guncelHastaListesi.size(); ++i) {
      const Randevu &r = guncelHastaListesi[i];
      ui->tableWidget->insertRow(i);
      ui->tableWidget->setItem(i, 0, new QTableWidgetItem(r.doktor));
      ui->tableWidget->setItem(i, 1, new QTableWidgetItem(r.ad));
      ui->tableWidget->setItem(i, 2, new QTableWidgetItem(r.saat));
      ui->tableWidget->setItem(i, 3, new QTableWidgetItem(r.tarih));
   }

   // Initialize selection
   if (!guncelHastaListesi.isEmpty())
      guncelHastaIndex = 0;
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

Queue<Randevu> *randevular::doktorKuyrugunuAl(const QString &doktorAdi) {
   qDebug() << "Check 1";
   if (!doktorKuyruklari) return nullptr;
   qDebug() << "Check 2";

   for (auto &pair : *doktorKuyruklari) {
      if (pair.first == doktorAdi)
         return &pair.second;
   }
   qDebug() << "Check 3";

   doktorKuyruklari->emplace_back(doktorAdi, Queue<Randevu>());
   qDebug() << "Check 4";
   return &doktorKuyruklari->back().second;
}