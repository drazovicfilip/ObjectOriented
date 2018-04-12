#ifndef BALL_H
#define BALL_H

#include "coordinate.h"
#include <QPainter>
#include "abstractball.h"

/**
 * @brief The ball class is an implementation of the abstract ball class. Nothing has changed.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * Each ball will have a given coordinate, velocity, mass, radius and colour.
 * Balls will render themselves.
 */


class Ball : public AbstractBall
{

public:
    Ball(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity);

};
#endif // BALL_H
