#ifndef STANDARDCURSORSTATE_H
#define STANDARDCURSORSTATE_H
#include "CursorState.h"

class StandardCursorState : public CursorState
{
public:
    StandardCursorState();
    virtual ~StandardCursorState(){}

    void processClickEvent(QMouseEvent *event){}
    void processReleaseEvent(QMouseEvent *event){}

    void draw(QPainter &p, QVector2D mousePos, Ball* m_ball);
};

#endif // STANDARDCURSORSTATE_H
