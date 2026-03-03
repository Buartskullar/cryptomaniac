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
