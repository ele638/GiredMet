/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDB_load;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *progressTitle;
    QPushButton *execButton;
    QPushButton *graphicsButton;
    QPushButton *openButton;
    QProgressBar *progressBar;
    QPushButton *exitButton;
    QLabel *progressCounter;
    QLabel *progressTimer;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(588, 170);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(588, 170));
        QIcon icon;
        icon.addFile(QStringLiteral("logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionDB_load = new QAction(MainWindow);
        actionDB_load->setObjectName(QStringLiteral("actionDB_load"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(400, 0));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        progressTitle = new QLabel(centralWidget);
        progressTitle->setObjectName(QStringLiteral("progressTitle"));

        gridLayout->addWidget(progressTitle, 3, 0, 1, 4, Qt::AlignVCenter);

        execButton = new QPushButton(centralWidget);
        execButton->setObjectName(QStringLiteral("execButton"));
        execButton->setEnabled(true);
        execButton->setDefault(false);
        execButton->setFlat(false);

        gridLayout->addWidget(execButton, 1, 1, 1, 1);

        graphicsButton = new QPushButton(centralWidget);
        graphicsButton->setObjectName(QStringLiteral("graphicsButton"));
        graphicsButton->setEnabled(true);

        gridLayout->addWidget(graphicsButton, 1, 2, 1, 1);

        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setEnabled(false);

        gridLayout->addWidget(openButton, 1, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setMinimumSize(QSize(0, 0));
        progressBar->setMaximumSize(QSize(16777214, 16777215));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        progressBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(progressBar, 6, 0, 1, 4, Qt::AlignBottom);

        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        gridLayout->addWidget(exitButton, 1, 3, 1, 1);

        progressCounter = new QLabel(centralWidget);
        progressCounter->setObjectName(QStringLiteral("progressCounter"));

        gridLayout->addWidget(progressCounter, 4, 0, 1, 4);

        progressTimer = new QLabel(centralWidget);
        progressTimer->setObjectName(QStringLiteral("progressTimer"));
        progressTimer->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(progressTimer, 5, 0, 1, 4);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 588, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GiredMet", 0));
        actionDB_load->setText(QApplication::translate("MainWindow", "load", 0));
        progressTitle->setText(QString());
        execButton->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214", 0));
        graphicsButton->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272", 0));
        openButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\244\320\260\320\271\320\273", 0));
        exitButton->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        progressCounter->setText(QString());
        progressTimer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
