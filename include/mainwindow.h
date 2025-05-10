#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include "queue.h"
#include "randevu.h"
#include "stack.h"
#include "DoubleLinkedList.h"
#include "randevular.h"

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
private:
    Queue<Randevu> bekleyenRandevular;

    QStack<Randevu> randevuStack;

    void randevuEkle();

    [[maybe_unused]] void sonrakiRandevu();

    void randevuSil();

    void randevuGoster();

    void randevuSorgula();

    void stackEkle();

    void stacktenCikar();

    void stackGoster();

    QString tarihSec();

    void sayfaGec();
};

#endif// MAINWINDOW_H
