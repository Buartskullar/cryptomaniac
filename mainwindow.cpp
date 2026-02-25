#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "crypto.h"

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

void MainWindow::on_pushButton_encrypter_clicked()
{
    QString output;
    output = cryops.encryptAtbash(ui->textEdit_input->toPlainText());
    ui->textEdit_output->setPlainText(output);
}

