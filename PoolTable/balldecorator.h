#ifndef BALLDECORATOR_H
#define BALLDECORATOR_H

#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QColor>

#include "ball.h"
#include "compositeball.h"

class BallDecorator : public Ball, public QWidget
{
    Ball* m_ball;

public:
    virtual ~BallDecorator(){
        //delete m_ball;
    }

    BallDecorator(Ball* ball);
    void draw(QPainter &p);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
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
    bool mouseReleased;
    QVector2D mousePosition;
};

#endif // BALLDECORATOR_H
