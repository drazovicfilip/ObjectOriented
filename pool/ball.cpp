#include "ball.h"

#include <cmath>
#include <string>

/**
 * @brief The ball class is an implementation of the abstract ball class. Nothing has changed.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * Each ball will have a given coordinate, velocity, mass, radius and colour.
 * Balls will render themselves.
 */

Ball::Ball(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity)
    : AbstractBall(coordinate, color, mass, radius, xVelocity, yVelocity)
{}
