#ifndef FACTORY_H
#define FACTORY_H

#include "coordinate.h"
#include "ball.h"
#include "table.h"

class AbstractFactory
{
public:
    virtual Ball* createBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity) = 0;
    virtual Table* createTable( float length, float height, float thickness, float space, float friction) = 0;
};

#endif // FACTORY_H
