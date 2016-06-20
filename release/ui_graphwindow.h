/********************************************************************************
** Form generated from reading UI file 'graphwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHWINDOW_H
#define UI_GRAPHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GraphWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *zoomout;
    QCustomPlot *plot;
    QPushButton *zoomin;

    void setupUi(QMainWindow *GraphWindow)
    {
        if (GraphWindow->objectName().isEmpty())
            GraphWindow->setObjectName(QStringLiteral("GraphWindow"));
        GraphWindow->resize(661, 514);
        GraphWindow->setMouseTracking(true);
        QIcon icon;
        icon.addFile(QStringLiteral("logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        GraphWindow->setWindowIcon(icon);
        centralwidget = new QWidget(GraphWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        zoomout = new QPushButton(centralwidget);
        zoomout->setObjectName(QStringLiteral("zoomout"));

        gridLayout->addWidget(zoomout, 1, 1, 1, 1);

        plot = new QCustomPlot(centralwidget);
        plot->setObjectName(QStringLiteral("plot"));

        gridLayout->addWidget(plot, 0, 0, 1, 2);

        zoomin = new QPushButton(centralwidget);
        zoomin->setObjectName(QStringLiteral("zoomin"));

        gridLayout->addWidget(zoomin, 1, 0, 1, 1);

        GraphWindow->setCentralWidget(centralwidget);

        retranslateUi(GraphWindow);

        QMetaObject::connectSlotsByName(GraphWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GraphWindow)
    {
        GraphWindow->setWindowTitle(QApplication::translate("GraphWindow", "Graphics", 0));
        zoomout->setText(QApplication::translate("GraphWindow", "-", 0));
        zoomin->setText(QApplication::translate("GraphWindow", "+", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphWindow: public Ui_GraphWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHWINDOW_H
