#include <QFile>
#include <QString>
#include <QMessageBox>
#include <database.h>
#include <QApplication>
#include <QDebug>
using namespace std;

// Считываение файла
void readFile(QString filename, int* counter){
    QFile inputFile(filename);
    int count=0;
    if (!inputFile.open(QIODevice::ReadOnly))
    {
        QMessageBox alert;
        alert.setText("Ошибка при открытии файла");
        alert.exec();
        qDebug() << "Ошибка при открытии файла";
    }else{
        init();
        QString line;
        while(!inputFile.atEnd()){
            line = inputFile.readLine();
            QStringList list = line.split(",");

            /* данные в файле представленны в формате $f,%f\n,
                значит надо делить строку по запятой
                (в типе float дробная часть отделяется запятой) */

            qApp->processEvents(); // системный метод, чтобы интерфейс не зависал во время чтения файла

            db_add("r", list.at(0).toDouble(0), "w", list.at(1).toDouble(0));

            count++;
        }
    }
    *counter=count; // вывод количества прочитанных строк
}
