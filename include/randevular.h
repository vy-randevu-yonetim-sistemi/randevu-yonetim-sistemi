#ifndef RANDEVULAR_H
#define RANDEVULAR_H

#include "randevu.h"

#include <QMainWindow>
#include <QQueue>

namespace Ui {
    class randevular;
}

class randevular : public QMainWindow {
Q_OBJECT

public:
    explicit randevular(QMainWindow *mainWindow, QWidget *parent = nullptr);

    ~randevular() override;

private:
    Ui::randevular *ui;

    QQueue<Randevu> bekleyenRandevular;

    QMainWindow *m_mainWindow;

    void hastaListele(const QString &doktorAdi);

    void geriSayfaGec();

    void sonrakiRandevu();

    void randevuGoster();


};

#endif// RANDEVULAR_H
