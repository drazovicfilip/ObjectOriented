#include "stage3ball.h"
#include <cmath>

void Stage3Ball::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}


CompositeStage3Ball::~CompositeStage3Ball()
{
    for(Ball * b: m_containedBalls)
    {
        delete b;
    }
}

ChangeInPoolGame CompositeStage3Ball::changeVelocity(const QVector2D &deltaV)
{
    float energyOfCollision = mass()*deltaV.lengthSquared();
    if(energyOfCollision>m_strength)
    {
        float energyPerBall = energyOfCollision/m_containedBalls.size();
        QVector2D pointOfCollision((-deltaV.normalized())*m_radius);
        //for each component ball
        for(Ball * b: m_containedBalls)
        {
            b->setVelocity(m_velocity + sqrt(energyPerBall/b->mass())*(b->position()-pointOfCollision).normalized());
            b->setPosition(m_position+b->position());
        }
        ChangeInPoolGame change({this},std::move(m_containedBalls));
        m_containedBalls.clear();
        return change;
    }
    m_velocity += deltaV;
    return ChangeInPoolGame();
}

float CompositeStage3Ball::mass() const
{
    return m_mass+m_containedMass;
}

CompositeStage3Ball* CompositeStage3Ball::clone(){

    CompositeStage3Ball* newball = new CompositeStage3Ball(*this);
    CompositeStage3Ball* tempball = new CompositeStage3Ball(*this);
    newball->eraseChildren();

    for (Ball *b : tempball->containedBalls()){
        newball->addBall(b->clone());
    }

    newball->setDrawChildren(getDrawChildren());

    return newball;
}

void CompositeStage3Ball::draw(QPainter &p)
{
    Stage3Ball::draw(p);

    if(drawChildren)
    {
        //recursively draw children, translating the painter
        //so that the children are drawn realative to the parent
        p.translate(m_position.toPointF());
        for(Ball * b: m_containedBalls)
        {
            b->draw(p);
        }
        p.translate(-m_position.toPointF());
    }

}

void CompositeStage3Ball::setRadius(float newRadius)
{
    if(m_radius==-1)
        m_radius = newRadius;
    else
    {
        float ratio = newRadius/radius();
        m_radius = newRadius;
        //recursively decrease the radius of children
        for(Ball * b: m_containedBalls)
        {
            b->setRadius(b->radius()*ratio);
            b->setPosition(b->position()*ratio);
        }
    }
}

ChangeInPoolGame SimpleStage3Ball::changeVelocity(const QVector2D &deltaV)
{
    if(mass()*deltaV.lengthSquared()>m_strength)
        return ChangeInPoolGame({this});
    m_velocity += deltaV;
    return ChangeInPoolGame();
}
