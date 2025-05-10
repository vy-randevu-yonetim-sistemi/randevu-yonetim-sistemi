z#ifndef RANDEVULAR_H
#define RANDEVULAR_H

#include <QMainWindow>
#include "QQueue"
#include "randevu.h"
#include "DoubleLinkedList.h"
#include "doktor.h"

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

   DoubleLinkedList<Doktor> doktorListesi;
   DoubleLinkedList<Doktor>::Node* aktifDoktor = nullptr;

   void hastaListele(const QString &doktorAdi);

   void geriSayfaGec();

   void sonrakiRandevu();

   void randevuGoster();


};



#endif// RANDEVULAR_H
