#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QString>

Enemy::Enemy(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(760,900);
    enemyImg=":/Image/Enemy.png";
    enemyTimer = new QTimer(this);

    connect(enemyTimer, SIGNAL(timeout()), this, SLOT(update()));
    enemyTimer->start(1000);
}

Enemy::~Enemy() {}

void Enemy::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(enemyImg);
    painter.drawPixmap(205,25,313,161,pix);
}
