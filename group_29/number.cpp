#include "number.h"
#include <iostream>

using namespace std;

Number::Number(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(760,900);
    Num[0]=":/Image/Number/0.png";
    Num[1]=":/Image/Number/1.png";
    Num[2]=":/Image/Number/2.png";
    Num[3]=":/Image/Number/3.png";
    Num[4]=":/Image/Number/4.png";
    Num[5]=":/Image/Number/5.png";
    Num[6]=":/Image/Number/6.png";
    Num[7]=":/Image/Number/7.png";
    Num[8]=":/Image/Number/8.png";
    Num[9]=":/Image/Number/9.png";

    QPainter painter(this);
    pix[0].load(Num[0]);
    pix[1].load(Num[1]);
    pix[2].load(Num[2]);
    pix[3].load(Num[3]);
    pix[4].load(Num[4]);
    pix[5].load(Num[5]);
    pix[6].load(Num[6]);
    pix[7].load(Num[7]);
    pix[8].load(Num[8]);
    pix[9].load(Num[9]);
}

Number::~Number(){}

void Number::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(733,860,24,36,pix[TimeLimit%10]);
    painter.drawPixmap(708,860,24,36,pix[TimeLimit/10%10]);
    painter.drawPixmap(683,860,24,36,pix[TimeLimit/100]);
}
