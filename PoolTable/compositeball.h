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
    CompositeBall(Ball* parent);

    // Ball interface
public:
    /**
     * @brief draw the ball
     * @param painter to use to draw the ball
     */
    void draw(QPainter &p);

    void setVelocity(const QVector2D &newVelocity);
    void changePosition(const QVector2D &deltaX);
    void changeVelocity(const QVector2D &deltaV);
    float mass()const;

    void addBall(Ball* b){ m_balls.push_back(b); }
    std::vector<Ball*> getBalls(){ return m_balls; }

    void setChildrenVisible(bool v){ m_childrenVisible = v; }
    bool childrenVisible(){ return m_childrenVisible; }

private:
    std::vector<Ball*> m_balls;
    bool m_childrenVisible;
};

#endif // COMPOSITEBALL_H
