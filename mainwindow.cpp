#include "mainwindow.h"
#include "QtWidgets"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    statusBar()->showMessage("Готов к работе");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QFileDialog::getOpenFileName(this,"Открытие файла",QDir::homePath(),"*.*");
    ui->progressTitle->setText("Чтение файла...");
    ui->progressBar->setRange(0,100000);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    for(int i=0; i<100000; i++){
        ui->progressBar->setValue(i);
        qApp->processEvents();
    }
    ui->progressTitle->setText("");
    ui->execButton->setEnabled(true);
    ui->progressBar->setVisible(false);
    statusBar()->showMessage("Файл загружен");
}

void MainWindow::on_exitButton_clicked()
{
    QCoreApplication::instance()->exit();
}


void MainWindow::on_execButton_clicked()
{
    ui->progressTitle->setText("Вычисление...");
    ui->progressBar->setRange(0,100000);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    for(int i=0; i<100000; i++){
        ui->progressBar->setValue(i);
        qApp->processEvents();
    }
    ui->progressTitle->setText("");
    ui->progressBar->setVisible(false);
    ui->graphicsButton->setEnabled(true);
    statusBar()->showMessage("Данные обработаны");
}
