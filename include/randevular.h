#ifndef RANDEVULAR_H
#define RANDEVULAR_H

#include <QMainWindow>

namespace Ui {
   class randevular;
}

class randevular : public QMainWindow {
   Q_OBJECT

public:
   explicit randevular(QWidget *parent = nullptr);
   ~randevular();

private:
   Ui::randevular *ui;
};

#endif// RANDEVULAR_H
