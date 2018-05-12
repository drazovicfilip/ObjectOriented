#ifndef CUEDECORATOR_H
#define CUEDECORATOR_H

#include "ball.h"

class CueDecorator : public Ball
{
    Ball *m_ball;
public:
    CueDecorator(Ball* ball);
    void draw(QPainter &p) override;
};

#endif // CUEDECORATOR_H
