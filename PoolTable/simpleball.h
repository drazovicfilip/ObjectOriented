#ifndef SIMPLEBALL_H
#define SIMPLEBALL_H

#include <QColor>
#include <QPainter>

#include "ball.h"

/**
 * @brief The SimpleBall class is a concrete version of the Ball class specific to stage one of the assignment
 */
class SimpleBall : public Ball
{
public:
    SimpleBall();

    // Ball interface
public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
    void draw(QPainter &p);

    virtual void setStrength(float strength){ m_strength = strength; }
    virtual float strength(){ return m_strength; }

private:
    float m_strength;
};

#endif // SIMPLEBALL_H
