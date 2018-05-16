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

    void setParent(bool value){ m_hasParent = value; }

private:
    bool m_hasParent;
};

#endif // LEAFBALL_H
