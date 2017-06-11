#include "role.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QString>

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
    QPainter painter(this);
    QPixmap pix;

    pix.load(roleImg);
    painter.drawPixmap(0,0,91,125,pix);
}

