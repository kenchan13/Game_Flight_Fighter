#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class Enemy : public QWidget
{
    Q_OBJECT
public:
    explicit Enemy(QWidget *parent = 0);
    ~Enemy();

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *enemyTimer;
    QString enemyImg;

};

#endif // ENEMY_H
