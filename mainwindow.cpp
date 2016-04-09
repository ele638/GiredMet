#include "mainwindow.h"
#include "graphwindow.h"
#include "core.h"
#include "database.h"
#include "QtWidgets"
#include <QWindow>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar()->showMessage("Готов к работе");
    ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Открытие файла",QDir::homePath(),"*.dpt");
    int counter=0;
    QProcess process;
    QStringList args;
    args << "-c" << "wc -l "+filename+" | grep -o '[0-9]*'";
    process.start("/bin/sh", args);
    process.waitForFinished(-1);
    int totalcount = QString(process.readAll()).toInt();
    statusBar()->showMessage("Чтение файла");
    ui->progressTitle->setText("Чтение файла "+filename);
    ui->openButton->setEnabled(false);
    ui->progressBar->setMaximum(totalcount);
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);
    if (db_init(true)){
        readFile(filename, &counter, ui->progressBar);
        ui->progressTitle->setText("");
        ui->openButton->setEnabled(true);
        ui->execButton->setEnabled(true);
        ui->progressBar->setVisible(false);
        statusBar()->showMessage("Прочитано "+QString::number(counter)+" строк");
    }else{
        QMessageBox msg;
        msg.setWindowTitle("Alert Database");
        msg.setText("Невозможно подключиться к серверу PostgreSQL"
                    "(возможно клиент настроен некорректно)"
                    "Попробовать подключить MySQL базу данных?"
                    "(это вызовет небольшое замедление программы)");
        msg.addButton(QMessageBox::Yes);
        msg.addButton(QMessageBox::No);
        int choice = msg.exec();
        if(choice == QMessageBox::Yes){
            if(db_init(false)){
                readFile(filename, &counter, ui->progressBar);
                ui->progressTitle->setText("");
                ui->openButton->setEnabled(true);
                ui->execButton->setEnabled(true);
                ui->progressBar->setVisible(false);
                statusBar()->showMessage("Прочитано "+QString::number(counter)+" строк");
            }else{
                QMessageBox msg;
                msg.setText("Невозможно подключить базу данных");
                msg.exec();
                db_close();
                QApplication::exit();
            }
        }else{
            db_close();
        }
    }
}


void MainWindow::on_execButton_clicked()
{
    ui->progressTitle->setText("Вычисление...");
    qApp->processEvents();

    ui->progressTitle->setText("");
    ui->graphicsButton->setEnabled(true);
    statusBar()->showMessage("Данные обработаны");
}

void MainWindow::on_exitButton_clicked()
{
    db_close();
    QApplication::exit();
}

void MainWindow::on_graphicsButton_clicked()
{
    GraphWindow *window = new GraphWindow;
    window->show();
}
