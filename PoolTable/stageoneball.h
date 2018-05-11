#ifndef STAGEONEBALL_H
#define STAGEONEBALL_H

#include <QColor>
#include <QPainter>

#include "ball.h"

/**
 * @brief The StageOneBall class is a concrete version of the Ball class specific to stage one of the assignment
 */
class StageOneBall : public Ball
{
public:
    StageOneBall();

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

#endif // STAGEONEBALL_H
