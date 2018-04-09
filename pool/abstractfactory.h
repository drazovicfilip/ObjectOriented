#ifndef FACTORY_H
#define FACTORY_H

#include "coordinate.h"
#include "ball.h"
#include "table.h"

class AbstractFactory
{
public:
    virtual Ball* createBall(Coordinate coordinate, std::string color, int mass, int radius, double xVelocity, double yVelocity) = 0;
    virtual Table* createTable(unsigned int length, unsigned int height, unsigned int thickness, unsigned int space, unsigned int friction) = 0;
};

#endif // FACTORY_H
