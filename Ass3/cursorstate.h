#ifndef CURSORSTATE_H
#define CURSORSTATE_H

#include "QMouseEvent"
#include "QPainter"
#include "ball.h"

class CursorState
{
public:
    CursorState(){}
    virtual ~CursorState(){}

    virtual void processClickEvent(QMouseEvent *event) = 0;
    virtual void processReleaseEvent(QMouseEvent *event) = 0;

    virtual void draw(QPainter &p, QVector2D mousePos, Ball* m_ball) = 0;
};

#endif // CURSORSTATE_H
