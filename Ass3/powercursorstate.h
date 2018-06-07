#ifndef POWERCURSORSTATE_H
#define POWERCURSORSTATE_H
#include "cursorstate.h"

class PowerCursorState : public CursorState
{
public:
    PowerCursorState();
    virtual ~PowerCursorState(){}
    void processClickEvent(QMouseEvent *event, QVector2D* mousePos, BallDecorator* dec, bool* clicked){}
    void processReleaseEvent(QMouseEvent *event){}

    void draw(QPainter &p, QVector2D mousePos, BallDecorator* dec, bool clicked);
};

#endif // POWERCURSORSTATE_H
