#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "crypto.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modeF = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_encrypter_clicked()
{
    QString output;
    if (isDecrypting()) {
        output = cryops.decryptAtbash(ui->textEdit_input->toPlainText());
    }
    else {
        output = cryops.encryptAtbash(ui->textEdit_input->toPlainText());
    }
    ui->textEdit_output->setPlainText(output);
}

bool MainWindow::isDecrypting(){
    if (ui->radioButton_decrypt->isChecked()) modeF = 1;
    else modeF = 0;
    return modeF;
}

void MainWindow::on_radioButton_decrypt_clicked()
{
    ui->pushButton_encrypter->setText("Дешифровать!");
}

void MainWindow::on_radioButton_encrypt_clicked()
{
    ui->pushButton_encrypter->setText("Зашифровать!");
}

