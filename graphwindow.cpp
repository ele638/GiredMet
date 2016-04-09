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
    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(ui->plot);
    ui->plot->addItem(textLabel);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("Maximum at ["+QString::number(getmax('x'))+":"+QString::number(getmax('y'))+"]");
    textLabel->setFont(QFont(font().family(), 16)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text
    // add the arrow:
    QCPItemLine *arrow = new QCPItemLine(ui->plot);
    ui->plot->addItem(arrow);
    arrow->start->setParentAnchor(textLabel->bottom);

    arrow->end->setCoords(getmaxi('x'), getmaxi('y')); // point to (4, 1.6) in x-y-plot coordinates
    arrow->setHead(QCPLineEnding::esSpikeArrow);
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
