#ifndef NUMBER_H
#define NUMBER_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class Number : public QWidget
{
    Q_OBJECT
public:
    explicit Number(QWidget *parent = 0);
    ~Number();
    int TimeLimit = 150;
    QPixmap pix[10];
protected:
    void paintEvent(QPaintEvent *);

private:
    QString Num[10];
};

#endif // NUMBER_H
