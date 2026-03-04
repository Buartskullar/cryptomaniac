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

    forSplit = QRegularExpression("[()]+");

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
        QString curKey = keys[listI];
        QString segment = input.mid(offset, curKey.length());
        if (segment.isEmpty()) break;
        offset += segment.length();
        for (int i = 0; i < segment.length(); i++){
            if (segment[i] == ' ') output.append(' ');
            output.append(segment[curKey[i].digitValue()-1]);
        }
    }
    for (int i = 0; i < spaces.size(); i++){
        output.insert(spaces[i], ' ');
    }
    return output;
}
