#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "crypto.h"

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

private:
    Ui::MainWindow *ui;
    crypto cryops;
    bool modeF;

    bool isDecrypting();
};
#endif // MAINWINDOW_H
