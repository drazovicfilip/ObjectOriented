#ifndef STANDARDCURSORSTATE_H
#define STANDARDCURSORSTATE_H
#include "CursorState.h"

class StandardCursorState : public CursorState
{
public:
    StandardCursorState();
    virtual ~StandardCursorState(){}

    void processClickEvent(QMouseEvent *event, QVector2D* mousePos, BallDecorator* dec, bool* clicked);
    void processReleaseEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball);
    void processMoveEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball){}


    void draw(QPainter &p, QVector2D mousePos, BallDecorator* dec, bool clicked);
};

#endif // STANDARDCURSORSTATE_H
