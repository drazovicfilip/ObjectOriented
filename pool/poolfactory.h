#ifndef POOLFACTORY_H
#define POOLFACTORY_H

#include "abstractfactory.h"

/**
 * @brief The PoolFactory is a concrete implementation of the abstract factory.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * It will make balls and a table.
 * It will be called upon by the builder (and thus by the director) when creating the pool game.
 */

class PoolFactory : public AbstractFactory
{
public:

    using AbstractFactory::createBall;
    Ball* createBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity) override{
        return new Ball(coordinate, color, mass, radius, xVelocity, yVelocity);
    }

    using AbstractFactory::createTable;
    Table* createTable(float length, float height, float thickness, float space, float friction, std::string color) override{
        return new Table(length, height, thickness, space, friction, color);
    }
};

#endif // POOLFACTORY_H
