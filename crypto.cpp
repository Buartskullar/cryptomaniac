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
        if (input[i] == ' ') output.append(' ');
        if ((alphRusCap.indexOf(input[i]) != -1) || (alphRusLow.indexOf(input[i]) != -1)){
                if (input[i].isUpper()){
                    output.append(alphRusCapRev[alphRusCap.indexOf(input[i])]);
                }
                if (input[i].isLower()){
                    output.append(alphRusLowRev[alphRusLow.indexOf(input[i])]);
                }
        }
        else {
            if (input[i].isUpper()){
                output.append(alphEngCapRev[alphEngCap.indexOf(input[i])]);
            }
            if (input[i].isLower()){
                output.append(alphEngLowRev[alphEngLow.indexOf(input[i])]);
            }
        }
    };
    return output;
}

