#ifndef POOLBUILDER_H
#define POOLBUILDER_H

#include "abstractbuilder.h"

class PoolBuilder : public AbstractBuilder
{
public:
    using AbstractBuilder::buildBall;
    virtual Ball* buildBall(Coordinate coordinate, std::string color, int mass, int radius, double xVelocity, double yVelocity);

    using AbstractBuilder::buildTable;
    virtual Table* buildTable(unsigned int length, unsigned int height, unsigned int thickness, unsigned int space, unsigned int friction);

    virtual Pool getPool();
};

#endif // POOLBUILDER_H
