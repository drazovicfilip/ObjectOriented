#ifndef POOLFACTORY_H
#define POOLFACTORY_H

#include "abstractfactory.h"

class PoolFactory : public AbstractFactory
{
public:

    using AbstractFactory::createBall;
    Ball* createBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity) override{
        return new Ball(coordinate, color, mass, radius, xVelocity, yVelocity);
    }

    using AbstractFactory::createTable;
    Table* createTable(float length, float height, float thickness, float space, float friction) override{
        return new Table(length, height, thickness, space, friction);
    }
};

#endif // POOLFACTORY_H
