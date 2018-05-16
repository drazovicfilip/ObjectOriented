#ifndef LEAFBALL_H
#define LEAFBALL_H

#include <QColor>
#include <QPainter>
#include <QMouseEvent>

#include "ball.h"
#include <vector>

class LeafBall : public Ball
{
public:
    LeafBall();

public:
    void draw(QPainter &p);

    void setParent(Ball* ball){ m_parent = ball; }

private:
    Ball* m_parent;
};

#endif // LEAFBALL_H
