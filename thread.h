#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QString>
#include <QVector>
#include "math.h"

class Thread : public QThread
{
public:
    // constructor
    // set name using initializer
    explicit Thread(QVector<double> all_R, QVector<double> all_w, int i);

    // overriding the QThread's run() method
    void run();
private:
    QVector<double> all_R, all_w;
    int i;
};

#endif // THREAD_H
