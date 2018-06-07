#ifndef CURSORSTATE_H
#define CURSORSTATE_H

#include "QMouseEvent"
#include "QPainter"
#include "ball.h"
#include "balldecorator.h"

class CursorState
{
public:
    CursorState(){}
    virtual ~CursorState(){}

    virtual void processClickEvent(QMouseEvent *event, QVector2D* mousePos, BallDecorator* dec, bool* clicked) = 0;
    virtual void processReleaseEvent(QMouseEvent *event) = 0;

    virtual void draw(QPainter &p, QVector2D mousePos, BallDecorator* dec, bool clicked) = 0;
};

#endif // CURSORSTATE_H
