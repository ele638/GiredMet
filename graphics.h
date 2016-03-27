#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "qcustomplot.h"

void initgraph();
void print(QCustomPlot *customPlot);
double getmax(char in);
double getmin(char in);
double getmaxi(char in);
#endif // GRAPHICS_H
