#include "crypto.h"

crypto::crypto() {
    alphEngCap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alphEngLow = "abcdefghijklmnopqrstuvwxyz";
    alphEngCapRev = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    alphEngLowRev = "zyxwvutsrqponmlkjihgfedcba";

    alphRusCap = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    alphRusLow = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    alphRusCapRev = "ЯЮЭЬЫЪЩШЧЦХФУТСРПОНМЛКЙИЗЖЁЕДГВБА";
    alphRusLowRev = "яюэьыъщшчцхфутсрпонмлкйизжёедгвба";

}

crypto::~crypto() {}

QString crypto::encryptAtbash(QString input){
    QString output = "";
    for (int i = 0; i < input.length(); i++){
        if ((alphRusCap.indexOf(input[i]) != -1) || (alphRusLow.indexOf(input[i]) != -1)){
                if (input[i].isUpper()){
                    output.append(alphRusCapRev[alphRusCap.indexOf(input[i])]);
                }
                if (input[i].isLower()){
                    output.append(alphRusLowRev[alphRusLow.indexOf(input[i])]);
                }
        }
        else if ((alphEngCap.indexOf(input[i]) != -1) || (alphEngLow.indexOf(input[i]) != -1)) {
            if (input[i].isUpper()){
                output.append(alphEngCapRev[alphEngCap.indexOf(input[i])]);
            }
            if (input[i].isLower()){
                output.append(alphEngLowRev[alphEngLow.indexOf(input[i])]);
            }
        }
        else output.append(input[i]);
    };
    return output;
}

QString crypto::decryptAtbash(QString input){
    QString output = "";
    for (int i = 0; i < input.length(); i++){
        if ((alphRusCap.indexOf(input[i]) != -1) || (alphRusLow.indexOf(input[i]) != -1)){
            if (input[i].isUpper()){
                output.append(alphRusCap[alphRusCapRev.indexOf(input[i])]);
            }
            if (input[i].isLower()){
                output.append(alphRusLow[alphRusLowRev.indexOf(input[i])]);
            }
        }
        else if ((alphEngCap.indexOf(input[i]) != -1) || (alphEngLow.indexOf(input[i]) != -1)) {
            if (input[i].isUpper()){
                output.append(alphEngCap[alphEngCapRev.indexOf(input[i])]);
            }
            if (input[i].isLower()){
                output.append(alphEngLow[alphEngLowRev.indexOf(input[i])]);
            }
        }
        else output.append(input[i]);
    };
    return output;
}

QString crypto::encryptCaesar(QString input, int offset){
    QString output = "";
    for (int i = 0; i < input.length(); i++){
        if ((alphRusCap.indexOf(input[i]) != -1) || (alphRusLow.indexOf(input[i]) != -1)){
            if (input[i].isUpper()){
                output.append(alphRusCap[(alphRusCap.indexOf(input[i])+offset)%alphRusCap.length()]);
            }
            if (input[i].isLower()){
                output.append(alphRusLow[(alphRusLow.indexOf(input[i])+offset)%alphRusLow.length()]);
            }
        }
        else if ((alphEngCap.indexOf(input[i]) != -1) || (alphEngLow.indexOf(input[i]) != -1)) {
            if (input[i].isUpper()){
                output.append(alphEngCap[(alphEngCap.indexOf(input[i])+offset)%alphEngCap.length()]);
            }
            if (input[i].isLower()){
                output.append(alphEngLow[(alphEngLow.indexOf(input[i])+offset)%alphEngCap.length()]);
            }
        }
        else output.append(input[i]);
    };
    return output;
}

QString crypto::decryptCaesar(QString input, int offset){
    QString output = "";
    for (int i = 0; i < input.length(); i++){
        if ((alphRusCap.indexOf(input[i]) != -1) || (alphRusLow.indexOf(input[i]) != -1)){
            if (input[i].isUpper()){
                output.append(alphRusCap[(alphRusCap.indexOf(input[i])-offset + alphRusCap.length())%alphRusCap.length()]);
            }
            if (input[i].isLower()){
                output.append(alphRusLow[(alphRusLow.indexOf(input[i])-offset + alphRusLow.length())%alphRusLow.length()]);
            }
        }
        else if ((alphEngCap.indexOf(input[i]) != -1) || (alphEngLow.indexOf(input[i]) != -1)) {
            if (input[i].isUpper()){
                output.append(alphEngCap[(alphEngCap.indexOf(input[i])-offset + alphEngCap.length())%alphEngCap.length()]);
            }
            if (input[i].isLower()){
                output.append(alphEngLow[(alphEngLow.indexOf(input[i])-offset + alphEngLow.length())%alphEngLow.length()]);
            }
        }
        else output.append(input[i]);
    };
    return output;
}

QList<QString> crypto::splitReshelye(const QString &input){
    static QRegularExpression forSplit("[()]+");
    return input.split(forSplit, Qt::SkipEmptyParts);
}

QList<int> crypto::spaceFinder(const QString &input){
    QList<int> spaces;
    for (int i = 0; i < input.length(); ++i) {
        if (input.at(i).isSpace()) {
            spaces.append(i); // Запоминаем индекс
        }
    }
    return spaces;
}

QString crypto::encryptReshelye(QString input, QString key){
    QString output = "";
    int offset = 0;
    QList<QString> keys = splitReshelye(key);
    QList<int> spaces = spaceFinder(input);
    input.remove(' ');
    for (int listI = 0; listI < keys.length(); listI++){
        QStringList curKey = keys[listI].split(",", Qt::SkipEmptyParts);
        QString segment = input.mid(offset, curKey.length());
        int threshold = segment.length();
        for (QString &num : curKey){
            if (num.toInt() > threshold) {
                return "Ошибка в наибольшей цифре ключа!";
            }
        }
        if (segment.isEmpty()) break;
        for (int i = 0; i < segment.length(); i++){
            if (segment[i] == ' ') output.append(' ');
            output.append(segment[curKey[i].toInt()-1]);
        }
        offset += segment.length();
        output.remove(' ');
    }
    for (int i = 0; i < spaces.size(); i++){
        output.insert(spaces[i], ' ');
    }
    return output;
}

QString crypto::decryptReshelye(QString input, QString key){
    QString output = "";
    int offset = 0;
    QList<QString> keys = splitReshelye(key);
    QList<int> spaces = spaceFinder(input);
    input.remove(' ');
    for (int listI = 0; listI < keys.length(); listI++){
        QStringList curKey = keys[listI].split(",", Qt::SkipEmptyParts);        QString segment = input.mid(offset, curKey.length());
        QString outSeg;
        outSeg.fill('.', segment.length());
        for (QString &num : curKey){
            if (num.toInt() > segment.length()) {
                return "Ошибка в наибольшей цифре ключа!";
            }
        }
        if (segment.isEmpty()) break;
        for (int i = 0; i < segment.length(); i++){
            if (segment[i] == ' ') outSeg[i] = ' ';
            outSeg[curKey[i].toInt()-1] = segment[i];
        }
        offset += segment.length();
        output.append(outSeg);
        output.remove(' ');
    }
    for (int i = 0; i < spaces.size(); i++){
        output.insert(spaces[i], ' ');
    }
    return output;
}

QString crypto::encryptGronsfeld(const QString input, const QString key) {
    if (key.isEmpty()) return input;

    QString result;
    int keyIndex = 0;

    for (const QChar &ch : input) {
        int shift = key[keyIndex % key.length()].digitValue();

        if (shift < 0) {
            result.append(ch);
            continue;
        }

        QString alph;

        if (alphEngCap.contains(ch)) alph = alphEngCap;
        else if (alphEngLow.contains(ch)) alph = alphEngLow;
        else if (alphRusCap.contains(ch)) alph = alphRusCap;
        else if (alphRusLow.contains(ch)) alph = alphRusLow;
        else {
            result.append(ch);
            continue;
        }

        int index = alph.indexOf(ch);
        int newIndex = (index + shift) % alph.length();

        result.append(alph[newIndex]);
        keyIndex++;
    }

    return result;
}

QString crypto::decryptGronsfeld(const QString input, const QString key) {
    if (key.isEmpty()) return input;

    QString result;
    int keyIndex = 0;

    for (const QChar &ch : input) {
        int shift = key[keyIndex % key.length()].digitValue();

        if (shift < 0) {
            result.append(ch);
            continue;
        }

        QString alph;

        if (alphEngCap.contains(ch)) alph = alphEngCap;
        else if (alphEngLow.contains(ch)) alph = alphEngLow;
        else if (alphRusCap.contains(ch)) alph = alphRusCap;
        else if (alphRusLow.contains(ch)) alph = alphRusLow;
        else {
            result.append(ch); // не буква
            continue;
        }

        int index = alph.indexOf(ch);

        int newIndex = (index - shift) % alph.length();

        if (newIndex < 0)
            newIndex += alph.length();

        result.append(alph[newIndex]);
        keyIndex++;
    }

    return result;
}

bool crypto::findAlphabet(QChar ch, const QString*& alpha, int& alphaLen, int& chIdx) const
{
    chIdx = alphEngCap.indexOf(ch);
    if (chIdx != -1) { alpha = &alphEngCap; alphaLen = alphEngCap.length(); return true; }

    chIdx = alphEngLow.indexOf(ch);
    if (chIdx != -1) { alpha = &alphEngLow; alphaLen = alphEngLow.length(); return true; }

    chIdx = alphRusCap.indexOf(ch);
    if (chIdx != -1) { alpha = &alphRusCap; alphaLen = alphRusCap.length(); return true; }

    chIdx = alphRusLow.indexOf(ch);
    if (chIdx != -1) { alpha = &alphRusLow; alphaLen = alphRusLow.length(); return true; }

    return false;
}

QString crypto::encryptVigenere(const QString& text, const QString& key)
{
    QString result;
    QString cleanKey;
    for (const QChar& k : key) {
        if (k.isLetter()) cleanKey.append(k);
    }
    if (cleanKey.isEmpty()) return text;

    int keyLen = cleanKey.length();
    int keyPos = 0;

    for (const QChar& ch : text) {
        const QString* alpha = nullptr;
        int alphaLen = 0;
        int chIdx = 0;

        if (!findAlphabet(ch, alpha, alphaLen, chIdx)) {
            result.append(ch);
            continue;
        }

        QChar keyChar = cleanKey[keyPos % keyLen];
        int shift = 0;

        QChar keyUpper = keyChar.toUpper();
        shift = alphEngCap.indexOf(keyUpper);
        if (shift == -1) {
            shift = alphRusCap.indexOf(keyUpper);
        }
        if (shift == -1) shift = 0;

        int newIdx = (chIdx + shift) % alphaLen;
        result.append(alpha->at(newIdx));

        keyPos++;
    }

    return result;
}

QString crypto::decryptVigenere(const QString& text, const QString& key)
{
    QString result;
    QString cleanKey;
    for (const QChar& k : key) {
        if (k.isLetter()) cleanKey.append(k);
    }
    if (cleanKey.isEmpty()) return text;

    int keyLen = cleanKey.length();
    int keyPos = 0;

    for (const QChar& ch : text) {
        const QString* alpha = nullptr;
        int alphaLen = 0;
        int chIdx = 0;

        if (!findAlphabet(ch, alpha, alphaLen, chIdx)) {
            result.append(ch);
            continue;
        }

        QChar keyChar = cleanKey[keyPos % keyLen];
        int shift = 0;
        QChar keyUpper = keyChar.toUpper();
        shift = alphEngCap.indexOf(keyUpper);
        if (shift == -1) shift = alphRusCap.indexOf(keyUpper);
        if (shift == -1) shift = 0;

        int newIdx = (chIdx - shift + alphaLen) % alphaLen;
        result.append(alpha->at(newIdx));

        keyPos++;
    }

    return result;
}
