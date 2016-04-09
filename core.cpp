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

double f (double x, void * params) {
  double alpha = *(double *) params;
  double f = log(alpha*x) / sqrt(x);
  return f;
}

void integral(){
    gsl_integration_workspace * w
        = gsl_integration_workspace_alloc (1000);

      double result, error;
      double expected = -4.0;
      double alpha = 1.0;

      gsl_function F;
      F.function = &f;
      F.params = &alpha;

      gsl_integration_qags (&F, 0, 1, 0, 1e-7, 1000,
                            w, &result, &error);
      QMessageBox msg;
      msg.setText(QString::number(result));
      msg.exec();
      gsl_integration_workspace_free (w);
}
