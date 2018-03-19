#ifndef BALL_H
#define BALL_H

#include "coordinate.h"
#include <QPainter>

class Ball
{

public:
    Ball(Coordinate coordinate);

    Ball(Coordinate coordinate,
        unsigned int radius);

    Ball(Coordinate coordinate,
        unsigned int radius,
        double gravity,
        double xVelocity,
        double yVelocity);

    virtual ~Ball(){}

    void render(QPainter &painter, unsigned int time);

    bool isCollision();

    unsigned int getRadius(){
        return m_radius;
    }

private:
    Ball();

    Coordinate m_coordinate;
    unsigned int m_radius;
    double m_gravity;
    double m_xVelocity;
    double m_yVelocity;
};

#endif // BALL_H
