#include "mainwindow.h"
#include "core.h"
#include "database.h"
#include "math.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
