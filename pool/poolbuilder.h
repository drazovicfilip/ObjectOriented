#ifndef POOLBUILDER_H
#define POOLBUILDER_H

#include "abstractbuilder.h"

class PoolBuilder : public AbstractBuilder
{
public:
    using AbstractBuilder::buildBall;
    virtual Ball* buildBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity);

    using AbstractBuilder::buildTable;
    virtual Table* buildTable(float length, float height, float thickness, float space, float friction);

    virtual Pool getPool();
};

#endif // POOLBUILDER_H
