#include "mainwindow.h"

#include <QApplication>




int main(int argc, char *argv[]) // викликаємо наше вікно
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
