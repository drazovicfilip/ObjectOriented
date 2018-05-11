#include "poolgame.h"
#include <math.h>

void PoolGame::simulateTimeStep(float timeStep)
{
    //collisions of balls with the edge of the table
    for(Ball * b: m_balls)
    {
        collision(*m_table,*b);
    }

    //a collision between each possible pair of balls
    for(int i = 0; i < m_balls.size();++i)
    {
        for(int j = i+1;j < m_balls.size();++j)
        {
            collision(*(m_balls[i]),*(m_balls[j]));
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
    for(Ball * b: m_balls)
    {
        b->draw(p);
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
    }
}

void PoolGame::collision(Table &t, Ball &b)
{
    //are we outside the bounds horizontally and getting further away?
    //if so reverse x velocity
    if((b.position().x()<b.radius() && b.velocity().x()<0) || (b.position().x()>t.width()-b.radius() && b.velocity().x()>0))
        b.changeVelocity(QVector2D(-b.velocity().x()*2,0));

    //same but vertical
    if((b.position().y()<b.radius() && b.velocity().y()<0) || (b.position().y()>t.height()-b.radius() && b.velocity().y()>0))
        b.changeVelocity(QVector2D(0,-b.velocity().y()*2));

}
