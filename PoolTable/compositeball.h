#ifndef COMPOSITEBALL_H
#define COMPOSITEBALL_H

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
    CompositeBall(bool hasParent);

    // Ball interface
public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
    void draw(QPainter &p);

    void addBall(Ball* b){ m_balls.push_back(b); }
    std::vector<Ball*> getBalls(){ return m_balls; }

    void setParent(bool value){ m_hasParent = value; }

private:
    bool m_hasParent;
    std::vector<Ball*> m_balls;
};

#endif // COMPOSITEBALL_H
