#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "crypto.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDesktopServices>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_encrypter_clicked();

    void on_radioButton_decrypt_clicked();

    void on_radioButton_encrypt_clicked();

    void on_explainButton_clicked();

private:
    Ui::MainWindow *ui;
    crypto cryops;


    bool modeF;
    int modeC;

    int isKeyValid(const QString &key);
    bool isDecrypting();
    void onListItemChanged(int row);

    void caesarUi(bool status);
    void reshelyeUi(bool status);

    QString encryptMaster();
    QString decryptMaster();

};
#endif // MAINWINDOW_H
