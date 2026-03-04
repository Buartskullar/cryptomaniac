#ifndef CRYPTO_H
#define CRYPTO_H
#include <QApplication>
#include <QRegularExpression>

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

    QRegularExpression forSplit;

    QList<QString> splitReshelye(const QString &input);
    QList<int> spaceFinder(const QString &input);

};


#endif // CRYPTO_H
