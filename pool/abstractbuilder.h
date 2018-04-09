#ifndef ABSTRACTBUILDER_H
#define ABSTRACTBUILDER_H

#include "ball.h"
#include "table.h"
#include "pool.h"

class AbstractBuilder
{
public:
    virtual Ball* buildBall(Coordinate coordinate, std::string color, int mass, int radius, double xVelocity, double yVelocity) = 0;
    virtual Table* buildTable(unsigned int length, unsigned int height, unsigned int thickness, unsigned int space, unsigned int friction) = 0;
    virtual Pool getPool() = 0;
};

#endif // ABSTRACTBUILDER_H
