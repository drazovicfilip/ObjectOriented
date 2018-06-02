#ifndef STAGE3BALL_H
#define STAGE3BALL_H
#include <vector>
#include <iostream>

#include "ball.h"
#include "QKeyEvent"
#include "changeinpoolgame.h"

/**
 * @brief The Stage3Ball class is the component in the composite design pattern
 * it contains the general stage 3 quality strength
 */
class Stage3Ball : public Ball, public QObject
{
public:
    Stage3Ball(){}

    Stage3Ball(QVector2D position, QVector2D velocity, float radius, float mass, QColor colour, float strength)
        : Ball(position, velocity, radius, mass, colour)
        , m_strength(strength)
    {}

    void setStrength(float strength){m_strength = strength;}

    float strength() const{ return m_strength; }
    // Ball interface
public:
    void draw(QPainter &p);

protected:
    float m_strength;
};

/**
 * @brief The CompositeBall class is the composite in the composite design pattern,
 * it stores a vector of children of type Stage3Ball. It can break apart to release these balls.
 */
class CompositeStage3Ball : public Stage3Ball
{
public:

    CompositeStage3Ball(CompositeStage3Ball const &ball)
        : Stage3Ball(ball.position(), ball.velocity(), ball.radius(), ball.mass(), ball.colour(), ball.strength())
        , m_containedBalls(ball.containedBalls())
        , m_containedMass(ball.containedMass())
        , drawChildren(ball.getDrawChildren())
    {}

    CompositeStage3Ball* clone();

    CompositeStage3Ball():m_containedMass(0)
    {
        Ball::setRadius(-1);
    }
    virtual ~CompositeStage3Ball();

    /**
     * @brief changeVelocity changes the velocity of the ball, if it changes to fast it may break apart
     * @param deltaV the change in velocity
     * @return the change to the poolgame list of balls, if the ball breaks it will be added to the remove list
     * and its children will be added to the add list
     */
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);

    /**
     * @brief mass get the total mass of the composite ball wich is the sum of its mass and the mass of its children
     * @return
     */
    float mass() const;

    /**
     * @brief draws the composite ball, if draw children is true it will also draw its children
     * @param p
     */
    void draw(QPainter &p);

    /**
     * @brief addBall to the composite
     * @param ball
     */
    void addBall(Ball* ball)
    {
        m_containedBalls.push_back(ball);
        m_containedMass += ball->mass();
    }

    /**
     * @brief setRadius sets the new radius of the ball, adjusting the radius of any children so they are stil contained
     * @param newRadius
     */
    void setRadius(float newRadius);

    std::vector<Ball*> containedBalls() const{ return m_containedBalls; }
    float containedMass() const{ return m_containedMass; }
    bool getDrawChildren() const{ return drawChildren; }
    bool setDrawChildren(bool v){ drawChildren = v; }
    void eraseChildren(){ m_containedBalls.erase(m_containedBalls.begin(), m_containedBalls.end()); }

protected:
    std::vector<Ball*> m_containedBalls;
    float m_containedMass;
    //here we decide whether or not to draw children
    bool drawChildren = true;
};

/**
 * @brief The SimpleStage3Ball class is the leaf in the composite design pattern,
 * all stage 3 balls that aren't composites are leaves
 */
class SimpleStage3Ball : public Stage3Ball
{
public:
    SimpleStage3Ball(){}

    SimpleStage3Ball* clone(){ return new SimpleStage3Ball(*this); }

    SimpleStage3Ball(SimpleStage3Ball const &ball)
        : Stage3Ball(ball.position(), ball.velocity(), ball.radius(), ball.mass(), ball.colour(), ball.strength())
    {}

    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);

};

#endif // STAGE3BALL_H
