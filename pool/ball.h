#ifndef BALL_H
#define BALL_H

#include "coordinate.h"
#include <QPainter>

enum BallType{ stripe, solid, cue, black };

class Ball
{

public:
    Ball(Coordinate coordinate);
    Ball(Coordinate coordinate, std::string color, BallType type);
    virtual ~Ball();
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
    std::string* m_color;
    BallType m_type;
};

#endif // BALL_H
