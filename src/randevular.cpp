#include "randevular.h"
#include "ui_randevular.h"
#include "QMessageBox"
#include "randevu.h"

randevular::randevular(QMainWindow* mainWindow, QWidget *parent)
    : QMainWindow(parent), m_mainWindow(mainWindow)
{
   ui = new Ui::randevular;
   ui->setupUi(this);

   connect(ui->btnAnaSayfa , &QPushButton::clicked , this , &randevular::geriSayfaGec);
   connect(ui->btnSonrakiRandevu, &QPushButton::clicked, this, &randevular::sonrakiRandevu);
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
