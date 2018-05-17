#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QVector2D>
#include <QColor>

#include "float.h"

/**
 * @brief The Ball class containes the logic and member variables of a circle representing a ball
 * concrete subclasses should override the draw function to enable drawing the ball
 */
class Ball
{
public:
    Ball()
    {}
    virtual ~Ball(){}

    /**
     * @brief position returns the current position of the ball
     * @return m_position (QVector2D)
     */
    virtual const QVector2D &position()const{ return m_position; }

    /**
     * @brief velocity returns the current velocity of the ball
     * @return m_velocity (QVector2D)
     */
    virtual const QVector2D &velocity()const{ return m_velocity; }

    /**
     * @brief radius returns the radius of the ball
     * @return radius (float)
     */
    virtual float radius()const{ return m_radius; }

    /**
     * @brief mass returns the mass of the ball
     * @return mass (float)
     */
    virtual float mass()const{ return m_mass; }

    /**
     * @brief setPosition sets the position manually to a QVector2D value
     * @param newPosition (QVector2D)
     */
    virtual void setPosition(const QVector2D &newPosition){ m_position = newPosition; }

    /**
     * @brief setVelocity sets the velocity manually to a QVector2D value.
     * @param newVelocity QVector2D)
     */
    virtual void setVelocity(const QVector2D &newVelocity){ m_velocity = newVelocity; }

    /**
     * @brief setRadius sets the radius manually to a value
     * @param newRadius (float)
     */
    virtual void setRadius(float newRadius){ m_radius = newRadius; }

    /**
     * @brief setMass sets the mass manually to a value
     * @param newMass (float)
     */
    virtual void setMass(float newMass){ m_mass = newMass; }

    /**
     * @brief changePosition adds a change to the current position
     * @param deltaX (QVector2D) - change to add
     */
    virtual void changePosition(const QVector2D &deltaX){ m_position += deltaX; }

    /**
     * @brief changeVelocity adds a change to the current velocity
     * @param deltaV (QVector2D) - change to add
     */
    virtual void changeVelocity(const QVector2D &deltaV){ m_velocity += deltaV; }

    /**
     * @brief draws the ball using the provided painter
     * @param p is the painter that is used to draw the object
     */
    virtual void draw(QPainter & p) = 0;

    /**
     * @brief moves the ball based on its current velocity
     * @param timestep is the ammount of time it should move for
     */
    virtual void move(float timestep){ changePosition(m_velocity*timestep); }

    /**
     * @brief strength returns the strength of the ball
     * @return strength (float)
     */
    virtual float strength(){ return m_strength; }

    /**
     * @brief setStrength sets the strength of the ball
     * @param strength (float)
     */
    virtual void setStrength(float strength){ m_strength = strength; }

    /**
     * @brief colour returns the colour of the ball (as QColor)
     * @return colour (QColor)
     */
    virtual QColor & colour(){ return m_colour; }

    /**
     * @brief setColour sets the colour manually to a value
     * @param newColour (QColor)
     */
    virtual void setColour(const QColor &newColour){ m_colour = newColour; }

protected:
    QVector2D m_position;
    QVector2D m_velocity;
    float m_radius;
    float m_mass;
    float m_strength = FLT_MAX;
    QColor m_colour;
};
#endif // BALL_H
