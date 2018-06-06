#ifndef POWERCURSORSTATE_H
#define POWERCURSORSTATE_H
#include "cursorstate.h"

class PowerCursorState : public CursorState
{
public:
    PowerCursorState();
    virtual ~PowerCursorState(){}
    void processClickEvent(QMouseEvent *event){}
    void processReleaseEvent(QMouseEvent *event){}

    void draw(QPainter &p, QVector2D mousePos, Ball* m_ball);
};

#endif // POWERCURSORSTATE_H
