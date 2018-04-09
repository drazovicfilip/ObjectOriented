#ifndef ABSTRACTBUILDER_H
#define ABSTRACTBUILDER_H

#include "ball.h"
#include "table.h"
#include "pool.h"

class AbstractBuilder
{
public:
    virtual Ball* buildBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity) = 0;
    virtual Table* buildTable(float length, float height, float thickness, float space, float friction) = 0;
    virtual Pool getPool() = 0;
};

#endif // ABSTRACTBUILDER_H

