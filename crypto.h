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
