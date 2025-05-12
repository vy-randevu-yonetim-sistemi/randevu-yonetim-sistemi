#ifndef RANDEVULAR_H
#define RANDEVULAR_H

#include "appointment.h"
#include "queue.h"
#include "stack.h"

#include <utility>
#include <vector>

#include <QMainWindow>
#include <QQueue>

namespace Ui {
   class randevular;
}

class randevular : public QMainWindow {
   Q_OBJECT

public:
   explicit randevular(QMainWindow *mainWindow,
                       std::vector<std::pair<QString, Queue<Randevu>>> *kuyruklar,
                       QWidget *parent = nullptr);
   ~randevular() override;

   Queue<Randevu> *doktorKuyrugunuAl(const QString &doktorAdi);

   [[nodiscard]] bool isAppointmentHandled(const Randevu &r) const;

private:
   std::vector<std::pair<QString, Queue<Randevu>>> *doktorKuyruklari = nullptr;
   QList<Randevu> guncelHastaListesi;
   int guncelHastaIndex = -1;
   QString aktifDoktor;

   QQueue<Randevu> bekleyenRandevular;
   Stack<Randevu> islenenRandevular;

   Randevu currentPatient;
   bool activePatient = false;

   Ui::randevular *ui = nullptr;
   QMainWindow *m_mainWindow = nullptr;

   void hastaBilgileriniGoster();
   void hastaListele(const QString &doktorAdi);
   void geriSayfaGec();
   void sonrakiRandevu();
   void oncekiRandevu();
   void randevuGoster();

public slots:
   void doktorDegisti(const QString &yeniDoktor);
};

#endif// RANDEVULAR_H