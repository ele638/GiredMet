#include "graphics.h"
#include "database.h"
#include "qcustomplot.h"

QVector <QVector <double> > inJm, inWR;
QVector<double> x_1, x_2, y_1, y_2 ;


void initgraph(){
        inJm = db_get_all_epsJm();
        x_1 = inJm[0];
        y_1 = inJm[1];
        inWR = db_get_all_W_R();
        x_2 = inWR[0];
        y_2 = inWR[1];

}

void print(QCustomPlot *customPlot){


    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->legend->setVisible(true);

    customPlot->graph(0)->addData(x_1, y_1);
    customPlot->graph(0)->setPen(QPen(QColor(255,10,0)));
    customPlot->graph(1)->addData(x_2, y_2);

    customPlot->graph(0)->setName("epsJm(w)");
    customPlot->graph(1)->setName("r(w)");
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(x_1.first(), x_1.last());
    customPlot->yAxis->setRange(y_1.first(), y_1.last());

    customPlot->replot();
}

