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

    const QColor & colour(){return m_colour;}
    void setColour(const QColor &newColour){m_colour = newColour;}

    // Ball interface
public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
    void draw(QPainter &p);

private:
    QColor m_colour;
};

#endif // STAGETWOBALL_H
