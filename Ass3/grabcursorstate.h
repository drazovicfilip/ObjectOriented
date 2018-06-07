#ifndef GRABCURSORSTATE_H
#define GRABCURSORSTATE_H
#include "cursorstate.h"
#include "vector"

class GrabCursorState : public CursorState
{
public:
    GrabCursorState();
    virtual ~GrabCursorState(){}
    void processClickEvent(QMouseEvent *event, QVector2D* mousePos, BallDecorator* dec, bool* clicked);
    void processReleaseEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball);
    void processMoveEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball);

    void draw(QPainter &p, QVector2D mousePos, BallDecorator* dec, bool clicked);

    void setFrame(size_t f){ frame = f; }
    size_t getFrame(){ return frame; }

    void setFrameDirection(bool d){ framedirection = d; }
    bool getFrameDirection(){ return framedirection; }

private:
    size_t frame;
    bool framedirection;
};

#endif // GRABCURSORSTATE_H

