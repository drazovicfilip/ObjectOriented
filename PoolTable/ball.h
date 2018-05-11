#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QVector2D>

/**
 * @brief The Ball class containes the logic and member variables of a circle representing a ball
 * concrete subclasses should override the draw function to enable drawing the ball
 */
class Ball
{
public:
    Ball(){}
    virtual ~Ball(){}

    const QVector2D &position()const{return m_position;}
    const QVector2D &velocity()const{return m_velocity;}
    float radius()const{return m_radius;}
    float mass()const{return m_mass;}

    void setPosition(const QVector2D &newPosition){m_position = newPosition;}
    /**
     * @brief setVelocity sets the velocity manually to a value.
     * This should only be used to initialize the balls starting velocity
     * and set it to zero if it is small enough, otherwise use changeVelocity
     * @param newVelocity
     */
    void setVelocity(const QVector2D &newVelocity){m_velocity = newVelocity;}
    void setRadius(float newRadius){m_radius = newRadius;}
    void setMass(float newMass){m_mass = newMass;}

    virtual void changePosition(const QVector2D &deltaX){m_position += deltaX;}
    virtual void changeVelocity(const QVector2D &deltaV){m_velocity += deltaV;}

    /**
     * @brief draws the ball using the provided painter
     * @param p is the painter that is used to draw the object
     */
    virtual void draw(QPainter & p) = 0;

    /**
     * @brief moves the ball based on its current velocity
     * @param timestep is the ammount of time it should move for
     */
    virtual void move(float timestep){changePosition(m_velocity*timestep);}

protected:
    QVector2D m_position;
    QVector2D m_velocity;
    float m_radius;
    float m_mass;
};
#endif // BALL_H
