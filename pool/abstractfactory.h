#ifndef FACTORY_H
#define FACTORY_H

#include "coordinate.h"
#include "ball.h"
#include "table.h"

/**
 * @brief The Factory is responsible for creating each object.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * This separates object creation from the client.
 * The client will only call the factory, not worrying about the concrete class implementation.
 */

class AbstractFactory
{
public:
    virtual Ball* createBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity) = 0;
    virtual Table* createTable( float length, float height, float thickness, float space, float friction, std::string color) = 0;
};

#endif // FACTORY_H
