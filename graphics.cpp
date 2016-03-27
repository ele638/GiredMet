#include "graphics.h"
#include "database.h"
#include "qcustomplot.h"

double xmax, ymax, xmin, ymin, maxi, mini;
QVector <QVector <double> > in;
QVector<double> x ;
QVector<double> y ;


void initgraph(){
    init();
    in = db_get_all("r", "w");
    x = in.at(0);
    y = in.at(1);
    xmax=x.at(0);
    xmin=x.at(1);
    ymax=y.at(0);
    ymin=y.at(1);
    for(int i=2; i<x.size(); i++){
        if (x.at(i)>xmax) xmax=x.at(i);
        if (y.at(i)>ymax) {
            ymax=y.at(i);
            maxi=i;
        }
        if (x.at(i)<xmin) xmin=x.at(i);
        if (y.at(i)<ymin) {
            ymin=y.at(i);
            mini=i;
        }
    }
}

void print(QCustomPlot *customPlot){


    customPlot->addGraph();

    customPlot->graph(0)->addData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(xmin, xmax);
    customPlot->yAxis->setRange(ymin, ymax);
    customPlot->replot();
}

double getmax(char in){
    return (in=='x'?xmax:ymax);
}

double getmin(char in){
    return (in=='x'?xmin:ymin);
}

double getmaxi(char in){
   return (in=='x'?x.at(maxi):ymax);
}
