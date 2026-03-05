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

    QRegularExpression rx("[1-9()]+");
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
    case 2:
        if (isKeyValid(ui->lineReshelye->text()) == 0)
        return cryops.encryptReshelye(ui->textEdit_input->toPlainText(), ui->lineReshelye->text());
        else return " ";
        break;
    default:
        return " ";
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
    case 2:
        if (isKeyValid(ui->lineReshelye->text()) == 0)
        return cryops.decryptReshelye(ui->textEdit_input->toPlainText(), ui->lineReshelye->text());
        else return " ";
        break;
    default:
        return "";
    }
}

int MainWindow::isKeyValid(const QString &key) {
    // 1. Проверка баланса и формата скобок через регулярное выражение
    // Проверяет, что строка состоит только из групп вида (1,2,3)
    static QRegularExpression formalRe(R"(^(\(\d+(,\d+)*\))+$)");
    if (!formalRe.match(key).hasMatch()) {
        ui->errorsReshelye->setText("Ошибка в скобках!");
        return 1;
    }

    // Разрезаем ключ на блоки: "(1,2)(3,4)" -> ["1,2", "3,4"]
    static QRegularExpression errorChecker("[()]+");
    QStringList blocks = key.split(errorChecker, Qt::SkipEmptyParts);
    int totalDigitsCount = 0;

    for (const QString &block : blocks) {
        QSet<int> uniqueNumbers; // Для поиска дубликатов внутри одной скобки

        for (const QChar &num : block) {
            int n = num.digitValue();
            totalDigitsCount++;

            // 2. Проверка на повторение чисел в пределах одной скобки
            if (uniqueNumbers.contains(n)) {
                ui->errorsReshelye->setText("Ошибка в дубликатах!");
                return 2;
            }
            uniqueNumbers.insert(n);
        }

        // 3. Проверка порога общего количества цифр
        if (totalDigitsCount > ui->textEdit_input->toPlainText().length()) {
            ui->errorsReshelye->setText("Ошибка в длине!");
            return 3;
        }
    }

    return 0;
}

void MainWindow::on_explainButton_clicked()
{
    QString linkAtbash = "https://ru.wikipedia.org/wiki/%D0%90%D1%82%D0%B1%D0%B0%D1%88";
    QString linkCaesar = "https://ru.wikipedia.org/wiki/%D0%A8%D0%B8%D1%84%D1%80_%D0%A6%D0%B5%D0%B7%D0%B0%D1%80%D1%8F";
    QString linkReshelye = "https://de.donstu.ru/CDOCourses/AII/POVT/%D0%9A%D0%BB%D0%B0%D1%81%D1%81%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B5%20%D1%88%D0%B8%D1%84%D1%80%D1%8B/11.html";
    switch (modeC) {
    case 0:
        QDesktopServices::openUrl(QUrl(linkAtbash));
        break;
    case 1:
        QDesktopServices::openUrl(QUrl(linkCaesar));
        break;
    case 2:
        QDesktopServices::openUrl(QUrl(linkReshelye));
        break;
    }
}

