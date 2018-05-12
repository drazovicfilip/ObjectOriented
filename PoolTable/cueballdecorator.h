#ifndef CUEBALLDECORATOR_H
#define CUEBALLDECORATOR_H

#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <iostream>

#include "ball.h"

class CueBallDecorator : public Ball, public QWidget
{
    Ball* m_ball;
public:
    CueBallDecorator(Ball* ball);
    void draw(QPainter &p);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CUEBALLDECORATOR_H
