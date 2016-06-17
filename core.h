#ifndef CORE_H
#define CORE_H
#include <QProgressBar>
#include <QLabel>
   int readFileSize(QString filename);
   void readFile(QString filename, QProgressBar* bar);
   double getint();
   bool getintegral(QProgressBar* bar, QLabel* label, QLabel* timer);
#endif // CORE_H
