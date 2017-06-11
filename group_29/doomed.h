#ifndef DOOMED_H
#define DOOMED_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>

class Doomed : public QWidget
{
    Q_OBJECT
public:
    explicit Doomed(QWidget *parent = 0);
    ~Doomed();
};

#endif // DOOMED_H
