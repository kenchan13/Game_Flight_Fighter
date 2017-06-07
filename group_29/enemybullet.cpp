#include "enemybullet.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QString>

enemybullet::enemybullet(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(760,900);
    bulletImg=":/Image/bullet.png";
    bulletTimer = new QTimer(this);

    connect(bulletTimer, SIGNAL(timeout()), this, SLOT(update()));
    bulletTimer->start(1000);
}

enemybullet::~enemybullet() {}

void enemybullet::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(bulletImg);
    painter.drawPixmap(-30,-30,25,25,pix);
}
