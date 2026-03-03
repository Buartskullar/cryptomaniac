#ifndef CRYPTO_H
#define CRYPTO_H
#include <QApplication>

class crypto
{
public:
    crypto();

    ~crypto();

    QString encryptAtbash(const QString input);
    QString decryptAtbash(const QString input);

    QString encryptCaesar(const QString input, const int offset);
    QString decryptCaesar(const QString input, const int offset);

    QString encryptReshelye(const QString input, const QString key);
    QString decryptReshelye(const QString input, const QString key);

private:
    QString alphEngCap;
    QString alphEngLow;
    QString alphEngCapRev;
    QString alphEngLowRev;

    QString alphRusCap;
    QString alphRusLow;
    QString alphRusCapRev;
    QString alphRusLowRev;

};


#endif // CRYPTO_H
