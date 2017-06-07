#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class enemybullet : public QWidget
{
    Q_OBJECT
public:
    explicit enemybullet(QWidget *parent = 0);
    ~enemybullet();

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer *bulletTimer;
    QString bulletImg;

};

#endif // ENEMYBULLET_H
