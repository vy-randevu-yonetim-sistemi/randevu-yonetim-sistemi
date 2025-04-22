#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>

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

private:
   void randevuEkle();
   void randevuSil();
   void randevuGoster();
   void randevuSorgula();
};
#endif// MAINWINDOW_H
