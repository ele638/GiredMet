#include "graphwindow.h"
#include "ui_graphwindow.h"
#include "qcustomplot.h"
#include "graphics.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    initgraph();
    print(ui->plot);
    ui->plot->setInteraction(QCP::iRangeDrag, true);
}



GraphWindow::~GraphWindow()
{
    delete ui;
}


void GraphWindow::on_zoomin_clicked()
{
    ui->plot->xAxis->scaleRange(0.5,0.0);
    ui->plot->yAxis->scaleRange(0.5,0.0);
    ui->plot->replot();
}

void GraphWindow::on_zoomout_clicked()
{
    ui->plot->xAxis->scaleRange(1.5,0.0);
    ui->plot->yAxis->scaleRange(1.5,0.0);
    ui->plot->replot();
}
