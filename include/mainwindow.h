#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include "appointment.h"
#include "queue.h"
#include "randevular.h"
#include "stack.h"

#include <utility>
#include <vector>

#include <QMainWindow>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui {
   class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);

   ~MainWindow() override;

private:
   Ui::MainWindow *ui;
   randevular *randevular_form;
   Queue<Randevu> &kuyrukOlustur(const QString &doktorAdi);

private:
   Queue<Randevu> bekleyenRandevular;
   QStack<Randevu> randevuStack;
   std::vector<std::pair<QString, Queue<Randevu>>> doktorKuyruklari;
   void randevuEkle();
   [[maybe_unused]] void sonrakiRandevu();
   void randevuSil();
   void randevuGoster();
   void randevuSorgula();
   void stackEkle();
   void stacktenCikar();
   void stackGoster();
   void sayfaGec();
   QString tarihSec();
};

#endif// MAINWINDOW_H
