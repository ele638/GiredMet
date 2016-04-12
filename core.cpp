#include <QFile>
#include <QString>
#include <QMessageBox>
#include <database.h>
#include <QApplication>
#include <QDebug>
#include <QProgressBar>
#include <math.h>
#include <gsl/gsl_integration.h>


using namespace std;

QVector<double> all_R;
QVector<double> all_w;
double Rw, Rw0, w0;

// Считываение файла
void readFile(QString filename, int* counter, QProgressBar* bar){
    QFile inputFile(filename);
    int count=0;
    if (!inputFile.open(QIODevice::ReadOnly))
    {
        QMessageBox alert;
        alert.setText("Ошибка при открытии файла");
        alert.exec();
        qDebug() << "Ошибка при открытии файла";
    }else{
        QString line;
        while(!inputFile.atEnd()){
            line = inputFile.readLine();
            QStringList list = line.split(",");

            /* данные в файле представленны в формате $f,%f\n,
                значит надо делить строку по запятой
                (в типе float дробная часть отделяется запятой) */

            // системный метод, чтобы интерфейс не зависал во время чтения файла
            if(!list.empty() && list.size()==2){
                db_add("r", list.at(0).toDouble(0), "w", list.at(1).toDouble(0));
                count++;
                bar->setValue(count);
            }
            qApp->processEvents();
        }
    }
    *counter=count; // вывод количества прочитанных строк
}

double f (double w, void * params) {

    double f = (log(all_R.value(all_w.indexOf(w))) - log(Rw0)) / (w - w0);
    return f;
}



void integral(){
      all_R = get_all_R();
      all_w = get_all_w();
      gsl_integration_workspace * w
        = gsl_integration_workspace_alloc (all_w.size());

      double result, error;
      w0 = all_w[0];
      Rw0 = get_R(w0);
      gsl_function F;
      F.function = &f;

      gsl_integration_qagp(&F, (double*) &all_w[0], (size_t) all_w.size(), 0, 1, all_w.size(),
                           w, &result, &error);
      QMessageBox msg;
      msg.setText(QString::number(result));
      msg.exec();
      gsl_integration_workspace_free (w);
}
