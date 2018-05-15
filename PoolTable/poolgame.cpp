#include "poolgame.h"
#include <math.h>

#include <iostream>
#include <balldecorator.h>
#include <compositeball.h>

void PoolGame::linkQWidgetParentToCueBall(QWidget* parent)
{
    for (Ball * b: m_balls)
    {
        if (b->colour() == QColor(Qt::white))
        {
            // Should this be dynamic_cast-ed?
            (dynamic_cast<BallDecorator*>(b))->setParent(parent);
            return;
        }
    }
}

void PoolGame::simulateTimeStep(float timeStep)
{
    //collisions of balls with the edge of the table
    for(Ball * b: m_balls)
    {
        collision(*m_table,*b);
    }

    //a collision between each possible pair of balls
    for(size_t i = 0; i < m_balls.size();++i)
    {
        for(size_t j = i+1;j < m_balls.size();++j)
        {
            collision(*(m_balls[i]),*(m_balls[j]));
        }

        for (size_t p = 0; p < m_pockets.size(); ++p)
        {
            collision(*(m_balls[i]), *(m_pockets[p]));
        }
    }

    for(Ball * b: m_balls)
    {
        b->move(timeStep);

        //apply friction
        b->changeVelocity(-m_table->friction()*timeStep*b->velocity());

        //if moving less than 5 pixels per second just stop
        if(b->velocity().length()<5)
            b->setVelocity(QVector2D(0,0));
    }
}

void PoolGame::draw(QPainter &p)
{

    m_table->draw(p);

    for(Pocket * pocket: m_pockets)
    {
        pocket->draw(p);
    }

    for(Ball * b: m_balls)
    {
        b->draw(p);
    }

}

void PoolGame::collision(Ball &b1, Pocket &p1)
{
    // Geometric distance formula
    float distance = sqrt( pow(b1.position().x() - p1.position().x(), 2) + pow(b1.position().y() - p1.position().y(), 2) );

    // The pocket has fully engulfed the ball
    if (distance + b1.radius() <= p1.radius()){
        deleteBall(b1);
    }
}

float PoolGame::ballStrength(Ball &b)
{
    CompositeBall* compositeball = (dynamic_cast<CompositeBall*>(&b));
    BallDecorator* decoratorball = (dynamic_cast<BallDecorator*>(&b));
    if (compositeball == nullptr)
    {
        return decoratorball->strength();
    }
    else
    {
        return compositeball->strength();
    }
}

void PoolGame::deleteBall(Ball &b)
{
    // Find the ball in the array of balls. If we found it, delete it
    for (size_t i = 0; i < m_balls.size(); ++i)
    {
        if (m_balls[i] == &b){
            m_balls.erase(m_balls.begin() + i);
            return;
        }
    }
}

void PoolGame::collision(Ball &b1, Ball &b2)
{

    //check if the distance between their centers is less than the sum of their radii
    if((b1.position()-b2.position()).length()<b1.radius()+b2.radius())
    {
        //using the code provided for the collision mechanics

         //calculate their mass ratio
         float mR = b2.mass() / b1.mass();

         //calculate the axis of collision
         QVector2D collisionVector = b2.position() - b1.position();
         collisionVector.normalize();

        //the proportion of each balls velocity along the axis of collision
         double vA = QVector2D::dotProduct(collisionVector, b1.velocity());
         double vB = QVector2D::dotProduct(collisionVector, b2.velocity());
         //the balls are moving away from each other so do nothing
         if (vA <= 0 && vB >= 0) {
          return;
         }

         //The velocity of each ball after a collision can be found by solving the quadratic equation
         //given by equating momentum and energy before and after the collision and finding the velocities
         //that satisfy this
         //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
         //first we find the discriminant
         double a = -(mR + 1);
         double b = 2 * (mR * vB + vA);
         double c = -((mR - 1) * vB * vB + 2 * vA * vB);
         double discriminant = sqrt(b * b - 4 * a * c);
         double root = (-b + discriminant)/(2 * a);
         //only one of the roots is the solution, the other pertains to the current velocities
         if (root - vB < 0.01) {
           root = (-b - discriminant)/(2 * a);
         }

         //The resulting changes in velocity for ball A and B
         b1.changeVelocity(mR * (vB - root) * collisionVector);
         b2.changeVelocity((root - vB) * collisionVector);

         if (m_stage == 2)
         {

             float velocityChangeB1 = sqrt(pow((mR * (vB - root) * collisionVector).x(),2) + pow((mR * (vB - root) * collisionVector).y(),2));
             float velocityChangeB2 = sqrt(pow(((root - vB) * collisionVector).x(),2) + pow(((root - vB) * collisionVector).y(),2));
             float kineticEnergyB1 = b1.mass() * pow(velocityChangeB1, 2);
             float kineticEnergyB2 = b2.mass() * pow(velocityChangeB2,2);
             float ballStrengthB1 = ballStrength(b1);
             float ballStrengthB2 = ballStrength(b2);

             if (kineticEnergyB1 >= ballStrengthB1)
             {
                 deleteBall(b1);
             }

             if (kineticEnergyB2 >= ballStrengthB2)
             {
                 deleteBall(b2);
             }
         }
    }
}

void PoolGame::collision(Table &t, Ball &b)
{
    bool collided = false;
    //are we outside the bounds horizontally and getting further away?
    //if so reverse x velocity
    if((b.position().x()<b.radius() && b.velocity().x()<0) || (b.position().x()>t.width()-b.radius() && b.velocity().x()>0))
    {
        b.changeVelocity(QVector2D(-b.velocity().x()*2,0));
        collided = true;
    }

    //same but vertical
    if((b.position().y()<b.radius() && b.velocity().y()<0) || (b.position().y()>t.height()-b.radius() && b.velocity().y()>0))
    {
        b.changeVelocity(QVector2D(0,-b.velocity().y()*2));
        collided = true;
    }

    if (collided == true && m_stage == 2)
    {
        float ballstrength = ballStrength(b);

        float velocityInitial = sqrt ( pow(b.velocity().x(),2) + pow(b.velocity().y(),2) );
        float velocityFinal = velocityInitial * -1.0;
        float kineticEnergy = b.mass() * pow(velocityInitial - velocityFinal, 2);

        // If the ball should break
        if (kineticEnergy >= ballstrength)
        {
            deleteBall(b);
        }
    }
}
