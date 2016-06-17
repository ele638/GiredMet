#include <QtWidgets>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <database.h>
#include <QApplication>
#include <QDebug>
#include <QProgressBar>
#include <QTime>
#include <math.h>

using namespace std;

QVector<double> all_R;
QVector<double> all_w;
QTime time;
QLabel* timer;

int readFileSize(QString filename){
    int count = 0;
    QFile inputFile(filename);
    if (!inputFile.open(QIODevice::ReadOnly))
    {
        QMessageBox alert;
        alert.setText("Ошибка при открытии файла");
        alert.exec();
        qDebug() << "Ошибка при открытии файла";
    }else{
        QString line;
        while(!inputFile.atEnd()){
            inputFile.readLine();
            count++;
        }
    }
    return count;
}

// Считываение файла
void readFile(QString filename, QProgressBar* bar){
    QFile inputFile(filename);
    int counter = 0;
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
            if(!list.empty() && list.size()==2){
                db_add(2 * M_PI *list.at(0).toDouble(0), list.at(1).toDouble(0));
                counter++;
                bar->setValue(counter);
                qApp->processEvents();
            }
        }
    }
    db_exec();
    qDebug("Файл считан");
}

double getint(QVector<double> arrR, QVector<double> arrW, unsigned int n, unsigned int i){
    double sum=0;
    unsigned int j=0;
    double y1, y2;
    double x1, x2;
    if (arrW[0]==arrW[i]){
        y1=(log(arrR[1])-log(arrR[i]))/(arrW[1]*arrW[1]-arrW[i]*arrW[i]);
        x1=arrW[1];
        j=2;
    }else{
        y1=(log(arrR[0])-log(arrR[i]))/(arrW[0]*arrW[0]-arrW[i]*arrW[i]);
        x1=arrW[0];
        j=1;
    }

    for(; j<n; j++){
        if (arrW[i]==arrW[j]) {
            continue;
        } //иначе деление на 0
        y2=(log(arrR[j])-log(arrR[i]))/(arrW[j]*arrW[j]-arrW[i]*arrW[i]);
        x2=arrW[j];
        sum+=(y1+y2)/2*(x2-x1);
        y1=y2;
        x1=x2;
        //printf("цикл x1=%f, y1= %f\n", x1, y1);
    }
    if(isnan(sum)){
         printf("NAN getint \n");
    }
    return sum;
}

//Коэфициент преломления n(w)
QVector<double> getN(QVector<double> arrTETA, QVector<double> arrR, unsigned int n, QProgressBar* bar, QLabel* label){
    QVector<double> arrN;
    unsigned int i;
    label->setText("N:");
    for(i=0; i<n; i++){
        arrN.push_back((1-arrR[i])/(1+arrR[i]-2*sqrt(arrR[i])*cos(arrTETA[i])));
        db_update(i+1, "n", arrN[i]);
        bar->setValue(n+i);
        timer->setText("Времени затрачено: " + QString::number(time.elapsed()/1000) + " секунд");
        qApp->processEvents();
    }
    return arrN;
}

//Коэфициент поглощения k(w)
QVector<double> getK(QVector<double> arrTETA, QVector<double> arrR, unsigned int n, QProgressBar* bar, QLabel* label){
    QVector<double> arrK;
    unsigned int i;
    label->setText("K:");
    for(i=0; i<n; i++){
        arrK.push_back((2*sqrt(arrR[i])*sin(arrTETA[i]))/(1+arrR[i]-2*sqrt(arrR[i])*cos(arrTETA[i])));
        db_update(i+1, "k", arrK[i]);
        bar->setValue(2*n+i);
        timer->setText("Времени затрачено: " + QString::number(time.elapsed()/1000) + " секунд");
        qApp->processEvents();
    }
    return arrK;
}

QVector<double> eps1(QVector<double> arrN, QVector<double> arrK, unsigned int n, QProgressBar* bar, QLabel* label){
    QVector<double> arrEPS1;
    unsigned int i;
    label->setText("EPS1:");
    for(i=0; i<n; i++){
        arrEPS1.push_back(arrN[i]*arrN[i]-arrK[i]*arrK[i]);
        db_update(i+1, "eps1", arrEPS1[i]);
        bar->setValue(3*n+i);
        timer->setText("Времени затрачено: " + QString::number(time.elapsed()/1000) + " секунд");
        qApp->processEvents();
    }
    return arrEPS1;
}

QVector<double> eps2(QVector<double> arrN, QVector<double> arrK, unsigned int n, QProgressBar* bar, QLabel* label){
    QVector<double> arrEPS2;
    unsigned int i;
    label->setText("EPS2:");
    for(i=0; i<n; i++){
        arrEPS2.push_back(2*arrN[i]*arrK[i]);
        db_update(i+1, "eps2", arrEPS2[i]);
        bar->setValue(4*n+i);
        timer->setText("Времени затрачено: " + QString::number(time.elapsed()/1000) + " секунд");
        qApp->processEvents();
    }
    return arrEPS2;
}

QVector<double> epsJm(QVector<double> arrEPS1, QVector<double> arrEPS2, unsigned int n, QProgressBar* bar, QLabel* label){
    QVector<double> arrJmE;
    unsigned int i;
    label->setText("EPSJM:");
    for(i=0; i<n; i++){
        arrJmE.push_back((arrEPS2[i])/(pow(arrEPS1[i], 2)+pow(arrEPS2[i], 2)));
        db_update(i+1, "epsJm", arrJmE[i]);
        bar->setValue(5*n+i);
        timer->setText("Времени затрачено: " + QString::number(time.elapsed()/1000) + " секунд");
        qApp->processEvents();
    }
    return arrJmE;
}

bool getintegral(QProgressBar *bar, QLabel* label, QLabel* intimer){
    time.start();
    timer = intimer;
    unsigned int i, n;
    QVector<double> arrTETHA, arrR, arrW, arrN, arrK, arrEPS1, arrEPS2, arrJmE;
    arrR = db_get_all_R();
    arrW = db_get_all_w();
    if (arrR.size() != arrW.size()) return false;
    n = arrR.size();
    bar->setMaximum(6*n);
    label->setText("Интеграл:");
    for (i=0; i<n; i++){
        arrTETHA.push_back(getint(arrR, arrW, n, i));
        arrTETHA[i] = -1*arrW[i]/M_PI*arrTETHA[i];
        arrTETHA[i] += -1/(2*M_PI)*(log(arrR[0]/arrR[i])*log(fabs((arrW[0]-arrW[i])/(arrW[0]+arrW[i])))-log(arrW[n-1]/arrW[i])*log(fabs((arrW[n-1]-arrW[i])/(arrW[n-1]+arrW[i]))));
        db_update(i, "tetha", arrTETHA[i]);
        bar->setValue(i);
        timer->setText("Времени затрачено: " + QString::number(time.elapsed()/1000) + " секунд");
        qApp->processEvents();
    }
    arrN = getN(arrTETHA, arrR, n, bar, label);
    arrK = getK(arrTETHA, arrR, n, bar, label);
    arrEPS1 = eps1(arrN, arrK, n, bar, label);
    arrEPS2 = eps2(arrN, arrK, n, bar, label);
    arrJmE = epsJm(arrEPS1, arrEPS2, n, bar, label);

    return true;
}

