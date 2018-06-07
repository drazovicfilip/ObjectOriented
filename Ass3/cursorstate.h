#ifndef CURSORSTATE_H
#define CURSORSTATE_H

#include "QMouseEvent"
#include "QPainter"
#include "ball.h"
#include "balldecorator.h"
#include "dialog.h"
#include "qapplication.h"

class CursorState
{
public:
    CursorState(){}
    virtual ~CursorState(){}

    virtual void processClickEvent(QMouseEvent *event, QVector2D* mousePos, BallDecorator* dec, bool* clicked) = 0;
    virtual void processReleaseEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball) = 0;
    virtual void processMoveEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball) = 0;

    virtual void draw(QPainter &p, QVector2D mousePos, BallDecorator* dec, bool clicked) = 0;
    virtual void setGame(PoolGame* game){ m_game = game; }

private:
    PoolGame* m_game;
};

#endif // CURSORSTATE_H
