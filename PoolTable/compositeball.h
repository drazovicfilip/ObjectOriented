#ifndef COMPOSITEBALL_H
#define COMPOSITEBALL_H

#include <QColor>
#include <QPainter>
#include <QMouseEvent>

#include "ball.h"
#include <vector>

/**
 * @brief The CompositeBall class is a concrete version of the Ball class. Everything is the same, except it also has children balls.
 */
class CompositeBall : public Ball
{
public:
    CompositeBall();

public:

    /**
     * @brief draw will draw the ball AND all of its children
     * @param p - painter to draw with
     */
    void draw(QPainter &p);

    /**
     * @brief setVelocity will set the velocity of the ball to a given value, and set all of its children to the same value so that they stay inside nicely
     * @param newVelocity
     */
    void setVelocity(const QVector2D &newVelocity);

    /**
     * @brief changePosition will change the position of the ball by a given value, and change the positions of the children by that same amount
     * @param deltaX
     */
    void changePosition(const QVector2D &deltaX);

    /**
     * @brief changeVelocity will change the velocity of the ball by a given value, and change the velocities of the children by that same amount
     * @param deltaV
     */
    void changeVelocity(const QVector2D &deltaV);

    /**
     * @brief mass returns the mass of the current ball and all of its children
     * @return the effective mass
     */
    float mass()const;

    /**
     * @brief addBall adds an additional ball into the children of the current ball
     * @param b - child to add
     */
    void addBall(Ball* b){ m_balls.push_back(b); }

    /**
     * @brief getBalls returns all the children of the current ball
     * @return m_balls - a vector of children ball pointers
     */
    std::vector<Ball*> getBalls(){ return m_balls; }

    /**
     * @brief setChildrenVisible makes all children visible/invisible based on a given bool (used in the draw function). This is set from the JSON file
     * @param v - given boolean
     */
    void setChildrenVisible(bool v){ m_childrenVisible = v; }

    /**
     * @brief childrenVisible returns if the children are visible or not
     * @return m_childrenVisible - boolean
     */
    bool childrenVisible(){ return m_childrenVisible; }

    /**
     * @brief toggleChildrenVisible will toggle visibility, used by the space bar (detected by the Dialog QWidget)
     */
    void toggleChildrenVisible(){ m_childrenVisible = !m_childrenVisible; }

private:
    std::vector<Ball*> m_balls;
    bool m_childrenVisible;
};

#endif // COMPOSITEBALL_H
