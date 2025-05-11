#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include "queue.h"
#include "randevu.h"
#include "stack.h"
#include "DoubleLinkedList.h"
#include "randevular.h"

#include <vector>
#include <utility>

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

    QString tarihSec();

    void sayfaGec();
};

#endif// MAINWINDOW_H
