#ifndef CompositeBall_H
#define CompositeBall_H

#include <QColor>
#include <QPainter>
#include <QMouseEvent>

#include "ball.h"
#include <vector>

/**
 * @brief The CompositeBall class is a concrete version of the Ball class specific to stage one of the assignment
 */
class CompositeBall : public Ball
{
public:
    CompositeBall();

    // Ball interface
public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
    void draw(QPainter &p);

    virtual void setStrength(float strength){ m_strength = strength; }
    virtual float strength(){ return m_strength; }

    void addBall(Ball* b){ m_balls.push_back(b); }
    std::vector<Ball*> getBalls(){ return m_balls; }

private:
    float m_strength;
    std::vector<Ball*> m_balls;
};

#endif // CompositeBall_H
