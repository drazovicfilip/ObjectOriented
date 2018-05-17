#ifndef BALLDECORATOR_H
#define BALLDECORATOR_H

#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QColor>

#include "ball.h"
#include "compositeball.h"


/**
 * @brief The BallDecorator class uses the Decorator design pattern to add additional functionality to a given ball.
 * Specifically, it will override the ball's draw method in order to draw more things - in this case, a cue which hits the ball.
 * It holds a ball as a member variable, and all of its methods just call that ball's methods. For information about the method,
 * have a look at the descriptions in ball.h
 */
class BallDecorator : public Ball, public QWidget
{
    Ball* m_ball;

public:
    virtual ~BallDecorator(){}

    BallDecorator(Ball* ball);

    /**
     * @brief draw will not only draw the sub-ball, but also draw a cue on top of it
     * @param p - painter to draw with
     */
    void draw(QPainter &p);

    /**
     * @brief mousePressEvent allows the BallDecorator class to handle mouse clicks. This is because it is a child of the QWidget Dialog
     * @param event - the mouse event, with a lot of information stored inside it
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mouseMoveEvent allows the BallDecorator class to handle mouse movement. This is because it is a child of the QWidget Dialog
     * @param event - the mouse event, with a lot of information stored inside it
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mouseReleaseEvent allows the BallDecorator class to handle mouse clicks. This is because it is a child of the QWidget Dialog
     * @param event - the mouse event, with a lot of information stored inside it
     */
    void mouseReleaseEvent(QMouseEvent *event);

    // Functions that call the sub-ball
    const QVector2D &position()const{ return m_ball->position(); }
    const QVector2D &velocity()const{ return m_ball->velocity(); }
    float radius() const { return m_ball->radius(); }
    float mass() const { return m_ball->mass(); }
    QColor &colour() { return m_ball->colour(); }
    void setPosition(const QVector2D &newPosition){ m_ball->setPosition(newPosition); }
    void setVelocity(const QVector2D &newVelocity){ m_ball->setVelocity(newVelocity); }
    void setRadius(float newRadius){ m_ball->setRadius(newRadius); }
    void setMass(float newMass){ m_ball->setMass(newMass); }
    void setColour(const QColor &newColour){ m_ball->setColour(newColour); }
    void changePosition(const QVector2D &deltaX){ m_ball->changePosition(deltaX); }
    void changeVelocity(const QVector2D &deltaV){ m_ball->changeVelocity(deltaV); }
    void move(float timestep){ m_ball->move(timestep); }
    void setStrength(float strength){ m_ball->setStrength(strength); }
    float strength(){ return m_ball->strength(); }

private:
    bool mousePressed;
    QVector2D mousePosition;
};

#endif // BALLDECORATOR_H
