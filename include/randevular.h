#ifndef RANDEVULAR_H
#define RANDEVULAR_H

#include <QMainWindow>
#include "QQueue"
#include "randevu.h"

namespace Ui {
   class randevular;
}

class randevular : public QMainWindow {
   Q_OBJECT

public:
   explicit randevular(QMainWindow* mainWindow, QWidget *parent = nullptr);
   ~randevular();


private:
   Ui::randevular *ui;

   QQueue<Randevu> bekleyenRandevular;

   QMainWindow* m_mainWindow;

   void hastaListele(const QString &doktorAdi);

   void geriSayfaGec();

   void sonrakiRandevu();

   void randevuGoster();


};

#endif// RANDEVULAR_H
