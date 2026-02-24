#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::textTransClick()
{
    QString extracted = ui->lineEdit->text();
    ui->textEdit->setText(extracted);
}

QString MainWindow::textEdit(QString input){
    return input;
}


void MainWindow::on_pushButton_clicked()
{
    QString extracted = ui->lineEdit->text();
    ui->textEdit->setText(extracted);
}

