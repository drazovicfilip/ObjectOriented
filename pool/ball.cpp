#include "ball.h"

#include <cmath>
#include <string>

// Standard constructor
Ball::Ball(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity)
    : AbstractBall(coordinate, color, mass, radius, xVelocity, yVelocity)
{}
