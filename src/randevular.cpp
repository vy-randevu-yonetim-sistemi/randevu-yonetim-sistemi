#include "randevular.h"
#include "ui_randevular.h"

randevular::randevular(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::randevular) {
   ui->setupUi(this);
}

randevular::~randevular() {
   delete ui;
}
