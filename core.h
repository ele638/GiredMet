#ifndef CORE_H
#define CORE_H
#include <QProgressBar>
#include <QLabel>
   int readFileSize(QString filename);
   void readFile(QString filename, int size, QProgressBar* bar);
   double getint();
   bool getintegral(QProgressBar* bar, QLabel* label);
#endif // CORE_H
