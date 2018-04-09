#ifndef POOLFACTORY_H
#define POOLFACTORY_H

#include "abstractfactory.h"

class PoolFactory : public AbstractFactory
{
public:

    using AbstractFactory::createBall;
    Ball* createBall(Coordinate coordinate, std::string color, int mass, int radius, double xVelocity, double yVelocity) override{
        return new Ball(coordinate, color, mass, radius, xVelocity, yVelocity);
    }

    using AbstractFactory::createTable;
    Table* createTable(unsigned int length, unsigned int height, unsigned int thickness, unsigned int space, unsigned int friction) override{
        return new Table(length, height, thickness, space, friction);
    }
};

#endif // POOLFACTORY_H
