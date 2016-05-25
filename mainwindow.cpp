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
    if(!db_connect()){
        QMessageBox msg;
        msg.setText("Невозможно подключить базу данных");
        msg.exec();
        db_close();
        QApplication::exit();
    }else{
        ui->openButton->setEnabled(true);
        statusBar()->showMessage("Готов к работе");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openButton_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,"Открытие файла",QDir::homePath(),"*.dpt");
    if (filename=="") return;
    db_init();
    int counter=readFileSize(filename);

    statusBar()->showMessage("Чтение файла");
    ui->progressTitle->setText("Чтение файла "+filename);

    ui->openButton->setEnabled(false);
    ui->execButton->setEnabled(false);
    ui->graphicsButton->setEnabled(false);

    ui->progressBar->setMaximum(counter);
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);

    readFile(filename, counter, ui->progressBar);

    ui->progressTitle->setText("");
    ui->progressCounter->setText("");
    ui->openButton->setEnabled(true);
    ui->execButton->setEnabled(true);
    ui->progressBar->setVisible(false);
    statusBar()->showMessage("Прочитано "+QString::number(counter)+" строк");
}


void MainWindow::on_execButton_clicked()
{  
    ui->openButton->setEnabled(false);
    ui->execButton->setEnabled(false);
    ui->graphicsButton->setEnabled(false);

    ui->progressTitle->setText("Вычисление...");
    statusBar()->showMessage("Обработка");
    ui->progressBar->setVisible(true);

    getintegral(ui->progressBar, ui->progressCounter);
    //integral(ui->progressBar);
    ui->progressTitle->setText("");
    ui->progressCounter->setText("");
    ui->progressBar->setVisible(false);

    ui->openButton->setEnabled(true);
    ui->execButton->setEnabled(true);
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

