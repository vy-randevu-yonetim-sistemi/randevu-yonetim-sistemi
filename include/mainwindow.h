#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include "queue.h"
#include "randevu.h"

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
    Queue<Randevu> bekleyenRandevular;

    void randevuEkle();

    void sonrakiRandevu();

    void randevuSil();

    void randevuGoster();

    void randevuSorgula();
};

#endif// MAINWINDOW_H
