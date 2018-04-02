#ifndef BALL_H
#define BALL_H

#include "coordinate.h"
#include <QPainter>

class Ball
{

public:
    Ball(Coordinate coordinate);

    virtual ~Ball(){}

    void render(QPainter &painter, unsigned int time);

    bool isCollision();

    unsigned int getRadius(){
        return m_radius;
    }

private:
    Coordinate m_coordinate;
    unsigned int m_radius;
    double m_xVelocity;
    double m_yVelocity;
};

#endif // BALL_H
