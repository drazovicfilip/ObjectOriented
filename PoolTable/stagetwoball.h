#ifndef STAGETWOBALL_H
#define STAGETWOBALL_H

#include <QColor>
#include <QPainter>
#include <QMouseEvent>

#include "ball.h"

/**
 * @brief The StageTwoBall class is a concrete version of the Ball class specific to stage one of the assignment
 */
class StageTwoBall : public Ball
{
public:
    StageTwoBall();

    // Ball interface
public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
    void draw(QPainter &p);

};

#endif // STAGETWOBALL_H
