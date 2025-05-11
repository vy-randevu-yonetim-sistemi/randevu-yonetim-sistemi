#ifndef RANDEVULAR_H
#define RANDEVULAR_H

#include "randevu.h"
#include "queue.h"

#include <vector>
#include <utility>

#include <QMainWindow>
#include <QQueue>

namespace Ui {
    class randevular;
}

class randevular : public QMainWindow {
Q_OBJECT

public:
   explicit randevular(QMainWindow *mainWindow, std::vector<std::pair<QString, Queue<Randevu>>> *kuyruklar, QWidget *parent = nullptr);

   Queue<Randevu> *doktorKuyrugunuAl(const QString &doktorAdi);

    ~randevular() override;

private:
   std::vector<std::pair<QString, Queue<Randevu>>> *doktorKuyruklari;

    QList<Randevu> guncelHastaListesi;
    int guncelHastaIndex = -1;
    void hastaBilgileriniGoster();

    Ui::randevular *ui;

    QQueue<Randevu> bekleyenRandevular;

    QMainWindow *m_mainWindow;

    void hastaListele(const QString &doktorAdi);

    void geriSayfaGec();

    void sonrakiRandevu();

    void randevuGoster();

    void oncekiRandevu();

    void oncekiIslem();

    void sonrakiIslem();

};

#endif// RANDEVULAR_H
