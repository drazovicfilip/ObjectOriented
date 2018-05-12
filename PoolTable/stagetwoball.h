#ifndef STAGETWOBALL_H
#define STAGETWOBALL_H

#include <QColor>
#include <QPainter>

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

    bool isCue() const { return m_isCue; }
    void setCue( bool isCue ) { m_isCue = isCue; }

    // Ball interface
public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
    void draw(QPainter &p);

private:
    QColor m_colour;
    bool m_isCue;
};

#endif // STAGETWOBALL_H
