#include "myDoubleSpinBox.h"

QString MyDoubleSpinBox::textFromValue(double value) const {
    QString result = "0" + QString::number((int)(value / 60)) + ":";

    int intPart = abs(value - value / 60);
    double restPart = (value - value / 60) - abs(value - value / 60);
    if (intPart > 9)
        result += (QString::number(intPart) + ".");
    else
        result += ("0" + QString::number(intPart) + ".");

    int rest = restPart * 1000;
    if (rest < 10)
        result = result + "00" + QString::number(rest);
    else if (rest < 100)
        result = result + "0" + QString::number(rest);
    else
        result += QString::number(rest);
        
    return result;
}

