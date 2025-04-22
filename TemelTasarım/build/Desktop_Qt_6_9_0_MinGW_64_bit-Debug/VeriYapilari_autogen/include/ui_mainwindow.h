/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QListView *listViewListe;
    QLabel *labelAd;
    QLineEdit *lineEditAd;
    QTextEdit *textEditListe;
    QLineEdit *lineEditSorgu;
    QPushButton *btnSorgu;
    QLineEdit *lineEditTC;
    QLabel *labelTC;
    QLineEdit *lineEditTarih;
    QLabel *labelTarih;
    QPushButton *btnEkle;
    QPushButton *btnSil;
    QPushButton *btnGoster;
    QComboBox *comboBoxSaat;
    QLabel *labelSorgu;
    QComboBox *comboBoxDoktor;
    QLabel *labelTarih_2;
    QLabel *labelDoktor;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1163, 853);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(380, 110, 291, 631));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        listViewListe = new QListView(layoutWidget);
        listViewListe->setObjectName("listViewListe");

        formLayout->setWidget(0, QFormLayout::ItemRole::SpanningRole, listViewListe);

        labelAd = new QLabel(layoutWidget);
        labelAd->setObjectName("labelAd");
        QFont font;
        font.setPointSize(12);
        labelAd->setFont(font);

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelAd);

        lineEditAd = new QLineEdit(layoutWidget);
        lineEditAd->setObjectName("lineEditAd");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEditAd);

        textEditListe = new QTextEdit(layoutWidget);
        textEditListe->setObjectName("textEditListe");

        formLayout->setWidget(10, QFormLayout::ItemRole::FieldRole, textEditListe);

        lineEditSorgu = new QLineEdit(layoutWidget);
        lineEditSorgu->setObjectName("lineEditSorgu");

        formLayout->setWidget(24, QFormLayout::ItemRole::FieldRole, lineEditSorgu);

        btnSorgu = new QPushButton(layoutWidget);
        btnSorgu->setObjectName("btnSorgu");

        formLayout->setWidget(25, QFormLayout::ItemRole::FieldRole, btnSorgu);

        lineEditTC = new QLineEdit(layoutWidget);
        lineEditTC->setObjectName("lineEditTC");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEditTC);

        labelTC = new QLabel(layoutWidget);
        labelTC->setObjectName("labelTC");
        labelTC->setFont(font);

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelTC);

        lineEditTarih = new QLineEdit(layoutWidget);
        lineEditTarih->setObjectName("lineEditTarih");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, lineEditTarih);

        labelTarih = new QLabel(layoutWidget);
        labelTarih->setObjectName("labelTarih");
        labelTarih->setFont(font);

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelTarih);

        btnEkle = new QPushButton(layoutWidget);
        btnEkle->setObjectName("btnEkle");

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, btnEkle);

        btnSil = new QPushButton(layoutWidget);
        btnSil->setObjectName("btnSil");

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, btnSil);

        btnGoster = new QPushButton(layoutWidget);
        btnGoster->setObjectName("btnGoster");

        formLayout->setWidget(9, QFormLayout::ItemRole::FieldRole, btnGoster);

        comboBoxSaat = new QComboBox(layoutWidget);
        comboBoxSaat->addItem(QString());
        comboBoxSaat->addItem(QString());
        comboBoxSaat->addItem(QString());
        comboBoxSaat->addItem(QString());
        comboBoxSaat->addItem(QString());
        comboBoxSaat->addItem(QString());
        comboBoxSaat->addItem(QString());
        comboBoxSaat->addItem(QString());
        comboBoxSaat->setObjectName("comboBoxSaat");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, comboBoxSaat);

        labelSorgu = new QLabel(layoutWidget);
        labelSorgu->setObjectName("labelSorgu");
        labelSorgu->setFont(font);

        formLayout->setWidget(24, QFormLayout::ItemRole::LabelRole, labelSorgu);

        comboBoxDoktor = new QComboBox(layoutWidget);
        comboBoxDoktor->addItem(QString());
        comboBoxDoktor->addItem(QString());
        comboBoxDoktor->addItem(QString());
        comboBoxDoktor->addItem(QString());
        comboBoxDoktor->addItem(QString());
        comboBoxDoktor->addItem(QString());
        comboBoxDoktor->setObjectName("comboBoxDoktor");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, comboBoxDoktor);

        labelTarih_2 = new QLabel(layoutWidget);
        labelTarih_2->setObjectName("labelTarih_2");
        labelTarih_2->setFont(font);

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, labelTarih_2);

        labelDoktor = new QLabel(layoutWidget);
        labelDoktor->setObjectName("labelDoktor");
        labelDoktor->setFont(font);

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, labelDoktor);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1163, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelAd->setText(QCoreApplication::translate("MainWindow", "Hasta Ad\304\261:", nullptr));
        btnSorgu->setText(QCoreApplication::translate("MainWindow", "Randevu Sorgula", nullptr));
        labelTC->setText(QCoreApplication::translate("MainWindow", "TC:", nullptr));
        labelTarih->setText(QCoreApplication::translate("MainWindow", "Tarih:", nullptr));
        btnEkle->setText(QCoreApplication::translate("MainWindow", "Randevu Ekle", nullptr));
        btnSil->setText(QCoreApplication::translate("MainWindow", "Randevu Sil", nullptr));
        btnGoster->setText(QCoreApplication::translate("MainWindow", "G\303\266ster", nullptr));
        comboBoxSaat->setItemText(0, QCoreApplication::translate("MainWindow", "08.00", nullptr));
        comboBoxSaat->setItemText(1, QCoreApplication::translate("MainWindow", "08.30", nullptr));
        comboBoxSaat->setItemText(2, QCoreApplication::translate("MainWindow", "09.00", nullptr));
        comboBoxSaat->setItemText(3, QCoreApplication::translate("MainWindow", "09.30", nullptr));
        comboBoxSaat->setItemText(4, QCoreApplication::translate("MainWindow", "10.00", nullptr));
        comboBoxSaat->setItemText(5, QCoreApplication::translate("MainWindow", "10.30", nullptr));
        comboBoxSaat->setItemText(6, QCoreApplication::translate("MainWindow", "11.00", nullptr));
        comboBoxSaat->setItemText(7, QCoreApplication::translate("MainWindow", "11.30", nullptr));

        labelSorgu->setText(QCoreApplication::translate("MainWindow", "Sorgu i\303\247in TC:", nullptr));
        comboBoxDoktor->setItemText(0, QCoreApplication::translate("MainWindow", "Has\304\261m Karatas\304\261m", nullptr));
        comboBoxDoktor->setItemText(1, QCoreApplication::translate("MainWindow", "Murat Kocataner", nullptr));
        comboBoxDoktor->setItemText(2, QCoreApplication::translate("MainWindow", "Yasin Aktarak", nullptr));
        comboBoxDoktor->setItemText(3, QCoreApplication::translate("MainWindow", "Ay\305\237e Tane", nullptr));
        comboBoxDoktor->setItemText(4, QCoreApplication::translate("MainWindow", "Ali Duraneller", nullptr));
        comboBoxDoktor->setItemText(5, QCoreApplication::translate("MainWindow", "Tahsin Munuro\304\237lu", nullptr));

        labelTarih_2->setText(QCoreApplication::translate("MainWindow", "Saat:", nullptr));
        labelDoktor->setText(QCoreApplication::translate("MainWindow", "Doktor:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
