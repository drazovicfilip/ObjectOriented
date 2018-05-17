#include "compositeball.h"
#include <iostream>
#include "float.h"

CompositeBall::CompositeBall()
{}

float CompositeBall::mass() const
{
    float mass = m_mass;
    for (size_t i = 0; i < m_balls.size(); i++)
    {
        mass = mass + m_balls[i]->mass();
    }
    return mass;
}

void CompositeBall::setVelocity(const QVector2D &newVelocity)
{
    m_velocity = newVelocity;
    std::vector<Ball*> b = getBalls();
    for (int i = 0; i < b.size() ; i++)
    {
        b[i]->setVelocity(newVelocity);
    }
}

void CompositeBall::changePosition(const QVector2D &deltaX)
{
    m_position += deltaX;
    std::vector<Ball*> b = getBalls();
    for (int i = 0; i < b.size() ; i++)
    {
        b[i]->changePosition(deltaX);
    }

}

void CompositeBall::changeVelocity(const QVector2D &deltaV)
{
    m_velocity += deltaV;
    std::vector<Ball*> b = getBalls();
    for (int i = 0; i < b.size() ; i++)
    {
        b[i]->changeVelocity(deltaV);
    }
}

void CompositeBall::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);

    if (m_childrenVisible)
    {
        // Draw each of the children as well
        std::vector<Ball*> b = getBalls();
        for (int i = 0; i < b.size() ; i++)
        {
            b[i]->draw(p);
        }
    }

}
