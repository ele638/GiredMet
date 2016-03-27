#include "mainwindow.h"
#include "core.h"
#include "QtWidgets"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar()->showMessage("Готов к работе");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Открытие файла",QDir::homePath(),"*.*");
    int counter=0;
    statusBar()->showMessage("Чтение файла");
    ui->progressTitle->setText("Чтение файла "+filename);
    ui->openButton->setEnabled(false);
    readFile(filename, &counter);
    ui->progressTitle->setText("");
    ui->openButton->setEnabled(true);
    ui->execButton->setEnabled(true);
    statusBar()->showMessage("Прочитано "+QString::number(counter)+" строк");

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
    QCoreApplication::instance()->exit();
}
