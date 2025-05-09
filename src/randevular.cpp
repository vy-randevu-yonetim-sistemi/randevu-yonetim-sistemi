#include "randevular.h"
#include "ui_randevular.h"
#include "QMessageBox"
#include "randevu.h"
#include "sqlite.h"
#include <QDate>
#include <QTime>

randevular::randevular(QMainWindow* mainWindow, QWidget *parent)
    : QMainWindow(parent), m_mainWindow(mainWindow)
{
   ui = new Ui::randevular;
   ui->setupUi(this);

   connect(ui->btnAnaSayfa , &QPushButton::clicked , this , &randevular::geriSayfaGec);
   connect(ui->btnSonrakiRandevu, &QPushButton::clicked, this, &randevular::sonrakiRandevu);
   connect(ui->pushButton_3, &QPushButton::clicked, this, &randevular::randevuGoster);
   connect(ui->comboBoxDoktor, &QComboBox::currentTextChanged, this, &randevular::hastaListele);
}


randevular::~randevular() {
   delete ui;
}


void randevular::geriSayfaGec(){
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


void randevular::randevuGoster()
{
   ui->tableWidget->setRowCount(0);

   QList<Randevu> randevular = SQLiteManager::instance().randevular();

   std::sort(randevular.begin(), randevular.end(), [](const Randevu& a, const Randevu& b) {
      QDate dateA = QDate::fromString(a.tarih, "ddd MMM d yyyy");
      QDate dateB = QDate::fromString(b.tarih, "ddd MMM d yyyy");

      if (dateA == dateB) {
         QTime timeA = QTime::fromString(a.saat, "HH:mm");
         QTime timeB = QTime::fromString(b.saat, "HH:mm");
         return timeA < timeB;
      }

      return dateA < dateB;
   });

   for (int i = 0; i < randevular.size(); ++i)
   {
      const Randevu& r = randevular[i];

      ui->tableWidget->insertRow(i);
      ui->tableWidget->setItem(i, 0, new QTableWidgetItem(r.tc));
      ui->tableWidget->setItem(i, 1, new QTableWidgetItem(r.ad));
      ui->tableWidget->setItem(i, 2, new QTableWidgetItem(r.tarih));
      ui->tableWidget->setItem(i, 3, new QTableWidgetItem(r.saat));
   }
}


void randevular::hastaListele(const QString &doktorAdi)
{
   QList<Randevu> hastalar = SQLiteManager::instance().randevularByDoktor(doktorAdi);

   ui->textEdit->clear();
   for (const Randevu& r : hastalar) {
      ui->textEdit->append(r.ad + " - " + r.tc + " - " + r.tarih + " " + r.saat+ " " + r.doktor);
   }
}
