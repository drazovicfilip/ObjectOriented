#include "compositeball.h"
#include <iostream>
#include "float.h"

CompositeBall::CompositeBall()
{}

float CompositeBall::mass() const{
    float mass = m_mass;

    // Add in the mass of all of the ball's children
    for (size_t i = 0; i < m_balls.size(); i++){
        mass = mass + m_balls[i]->mass();
    }
    return mass;
}

void CompositeBall::setVelocity(const QVector2D &newVelocity){
    m_velocity = newVelocity;

    // Set all of the children as well (they just follow the same velocity as the parent)
    std::vector<Ball*> b = getBalls();
    for (size_t i = 0; i < b.size() ; i++){
        b[i]->setVelocity(newVelocity);
    }
}

void CompositeBall::changePosition(const QVector2D &deltaX){
    m_position += deltaX;

    // Move all of the children as well (they just follow the parent)
    std::vector<Ball*> b = getBalls();
    for (size_t i = 0; i < b.size() ; i++){
        b[i]->changePosition(deltaX);
    }

}

void CompositeBall::changeVelocity(const QVector2D &deltaV){
    m_velocity += deltaV;
    std::vector<Ball*> b = getBalls();

    // Change all of the children as well (they just follow the same velocity as the parent)
    for (size_t i = 0; i < b.size() ; i++){
        b[i]->changeVelocity(deltaV);
    }
}

void CompositeBall::draw(QPainter &p){
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
    if (m_childrenVisible){

        // Draw each of the children as well
        std::vector<Ball*> b = getBalls();
        for (size_t i = 0; i < b.size() ; i++){
            b[i]->draw(p);
        }
    }
}
