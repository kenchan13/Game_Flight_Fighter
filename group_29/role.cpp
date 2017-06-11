#include "role.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <iostream>
using namespace std;

ROLE::ROLE(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(760,900);
    roleImg=":/Image/role.png";
    roleTimer = new QTimer(this);

    connect(roleTimer, SIGNAL(timeout()), this, SLOT(update()));
    roleTimer->start(1000);
}

ROLE::~ROLE() {}

void ROLE::paintEvent(QPaintEvent *)
{
    cout << "player->paintevent" << endl;
    QPainter painter(this);
    QPixmap pix;

    pix.load(roleImg);
    painter.drawPixmap(320,750,91,125,pix);
}

