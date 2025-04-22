#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
   QApplication Application(argc, argv);
   MainWindow Window;
   Window.show();
   return QApplication::exec();
}
