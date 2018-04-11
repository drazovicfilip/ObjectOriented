#ifndef BALL_H
#define BALL_H

#include "coordinate.h"
#include <QPainter>
#include "abstractball.h"

class Ball : public AbstractBall
{

public:
    Ball(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity);

};
#endif // BALL_H
