TEMPLATE = app
CONFIG += console c++11
QT += core gui widgets network sql

INCLUDEPATH += include
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/socket.cpp \
    src/sqlite.cpp

HEADERS += \
    include/mainwindow.h \
    include/socket.h \
    include/sqlite.h \
    include/randevu.h \
    include/queue.h \
    include/heap.h

FORMS += \
    src/mainwindow.ui
