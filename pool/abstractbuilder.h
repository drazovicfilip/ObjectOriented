#ifndef ABSTRACTBUILDER_H
#define ABSTRACTBUILDER_H

#include "ball.h"
#include "table.h"
#include "pool.h"

/**
 * @brief The Builder is responsible for building each object for the pool game.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * In this case, it will build the ball(s), table and the pool game itself.
 * The director will put them all together.
 */

class AbstractBuilder
{
public:
    virtual Ball* buildBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity) = 0;
    virtual Table* buildTable(float length, float height, float thickness, float space, float friction, std::string color) = 0;
    virtual Pool getPool() = 0;
};

#endif // ABSTRACTBUILDER_H

