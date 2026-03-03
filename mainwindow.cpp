#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "crypto.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modeF = 0;
    modeC = 0;
    ui->listModes->addItem("Атбаш");
    ui->listModes->addItem("Цезарь");
    ui->listModes->addItem("Ришелье");

    caesarUi(false);
    reshelyeUi(false);

    connect(ui->listModes, &QListWidget::currentRowChanged,
            this, &MainWindow::onListItemChanged);

    QRegularExpression rx("[0-9()]+");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineReshelye->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_encrypter_clicked()
{
    QString output;
    if (isDecrypting()) {
        output = decryptMaster();
    }
    else {
        output = encryptMaster();
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

void MainWindow::caesarUi(bool status){
    ui->labelOffset->setVisible(status);
    ui->spinOffset->setVisible(status);
}

void MainWindow::reshelyeUi(bool status){
    ui->labelReshelye->setVisible(status);
    ui->lineReshelye->setVisible(status);
}

void MainWindow::onListItemChanged(int row){
    switch (row) {
    case 0:
        modeC = 0;
        caesarUi(false);
        reshelyeUi(false);
        break;
    case 1:
        modeC = 1;
        caesarUi(true);
        reshelyeUi(false);
        break;
    case 2:
        modeC = 2;
        caesarUi(false);
        reshelyeUi(true);
        break;
    default:
        break;
    }
}

QString MainWindow::encryptMaster(){
    switch (modeC) {
    case 0:
        return cryops.encryptAtbash(ui->textEdit_input->toPlainText());
        break;
    case 1:
        return cryops.encryptCaesar(ui->textEdit_input->toPlainText(), ui->spinOffset->value());
        break;
    default:
        return "";
    }
}

QString MainWindow::decryptMaster(){
    switch (modeC) {
    case 0:
        return cryops.decryptAtbash(ui->textEdit_input->toPlainText());
        break;
    case 1:
        return cryops.decryptCaesar(ui->textEdit_input->toPlainText(), ui->spinOffset->value());
        break;
    default:
        return "";
    }
}
