#include "poolgame.h"
#include <math.h>

#include <iostream>
#include <balldecorator.h>
#include <leafball.h>
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
        //std::cout << "Drawing M" << b->mass() << " at (" << b->position().x() << ", " << b->position().y() << ") with velocity (" << b->velocity().x() << ", " << b->velocity().y() << ") and radius " << b->radius() << std::endl;
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

void PoolGame::deleteBall(Ball &b)
{
    // Find the ball in the array of balls. If we found it, delete it
    for (size_t i = 0; i < m_balls.size(); ++i)
    {
        if (m_balls[i] == &b){

            CompositeBall * compositeball = dynamic_cast<CompositeBall*>(&b);
            // If the ball we're dealing with is composite, we have to deal with its children. The cue ball (decorator) can never have children
            if (compositeball != nullptr)
            {
                for (size_t j = 0; j < compositeball->getBalls().size(); j++)
                {
                    m_balls.push_back(compositeball->getBalls()[j]);
                }
            }

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

         QVector2D preCollisionVelocityB1 = b1.velocity();
         QVector2D preCollisionVelocityB2 = b2.velocity();
         QVector2D velocityChangeB1 = mR * (vB - root) * collisionVector;
         QVector2D velocityChangeB2 = (root - vB) * collisionVector;

         //The resulting changes in velocity for ball A and B
         b1.changeVelocity(velocityChangeB1);
         b2.changeVelocity(velocityChangeB2);

         if (m_stage == 2)
         {
             float kineticEnergyB1 = b1.mass() * velocityChangeB1.lengthSquared();
             float kineticEnergyB2 = b2.mass() * velocityChangeB2.lengthSquared();

             size_t numComponentBallsB1 = 0;
             size_t numComponentBallsB2 = 0;

             CompositeBall* compositeball1 = dynamic_cast<CompositeBall*>(&b1);
             CompositeBall* compositeball2 = dynamic_cast<CompositeBall*>(&b2);

             if (compositeball1 != nullptr)
             {
                 numComponentBallsB1 = compositeball1->getBalls().size();
             }
             if (compositeball2 != nullptr)
             {
                 numComponentBallsB2 = compositeball2->getBalls().size();
             }

             if (kineticEnergyB1 >= b1.strength())
             {
                 float radius = b1.radius();
                 QVector2D position = b1.position();
                 deleteBall(b1);

                 for (size_t i = 0; i < numComponentBallsB1; i++)
                 {

                     float energyPerBall = kineticEnergyB1/numComponentBallsB1;
                     QVector2D pointOfCollision((-velocityChangeB1.normalized())*radius);

                     //for each component ball
                     QVector2D componentBallVelocity = preCollisionVelocityB1 + sqrt(energyPerBall/(compositeball1->getBalls()[i]->mass()))*((compositeball1->getBalls()[i]->position() - position)-pointOfCollision).normalized();
                     (compositeball1->getBalls()[i])->setVelocity(componentBallVelocity);
                }
             }

             if (kineticEnergyB2 >= b2.strength())
             {
                 float radius = b2.radius();
                 QVector2D position = b2.position();
                 deleteBall(b2);

                 for (size_t i = 0; i < numComponentBallsB2; i++)
                 {
                     float energyPerBall = kineticEnergyB2/numComponentBallsB2;
                     QVector2D pointOfCollision((-velocityChangeB2.normalized())*radius);

                     //for each component ball
                     QVector2D componentBallVelocity = preCollisionVelocityB2 + sqrt(energyPerBall/(compositeball2->getBalls()[i]->mass()))*((compositeball2->getBalls()[i]->position() - position)-pointOfCollision).normalized();
                     compositeball2->getBalls()[i]->setVelocity(componentBallVelocity);
                 }
             }
         }
    }
}

void PoolGame::collision(Table &t, Ball &b)
{
    bool collided = false;
    //are we outside the bounds horizontally and getting further away?
    //if so reverse x velocity

    QVector2D velocityChange = QVector2D(0,0);
    QVector2D preCollisionVelocity = b.velocity();

    if((b.position().x()<b.radius() && b.velocity().x()<0) || (b.position().x()>t.width()-b.radius() && b.velocity().x()>0))
    {
        if (m_stage == 1)
        {
            b.changeVelocity(QVector2D(-b.velocity().x()*2, 0));
        }
        velocityChange = QVector2D(-b.velocity().x()*2, 0);
        collided = true;
    }

    //same but vertical
    if((b.position().y()<b.radius() && b.velocity().y()<0) || (b.position().y()>t.height()-b.radius() && b.velocity().y()>0))
    {
        if (m_stage == 1)
        {
            b.changeVelocity(QVector2D(0,-b.velocity().y()*2));
        }
        velocityChange = QVector2D(0, -b.velocity().y()*2);
        collided = true;
    }

    if (collided == true && m_stage == 2)
    {
        float kineticEnergy = b.mass() * velocityChange.lengthSquared();

        std::cout << b.strength() << ", " << kineticEnergy << std::endl;

        // If the ball should break
        if (kineticEnergy >= b.strength())
        {
            size_t numComponentBalls = 0;
            CompositeBall* compositeball = dynamic_cast<CompositeBall*>(&b);
            if (compositeball != nullptr)
            {
                numComponentBalls = compositeball->getBalls().size();
            }

            float radius = b.radius();
            QVector2D position = b.position();
            deleteBall(b);

            for (size_t i = 0; i < numComponentBalls; i++)
            {
                float energyPerBall = kineticEnergy/numComponentBalls;
                QVector2D pointOfCollision((-velocityChange.normalized())*radius);

                std::cout << "Shatter Table with B" << i << ", point of collision: (" << pointOfCollision.x() << "," << pointOfCollision.y() << ") pre collision V: (" << preCollisionVelocity.x() << "," << preCollisionVelocity.y() << "), velocity change: (" << velocityChange.x() << ", " << velocityChange.y() << ")" << std::endl;
                std::cout << "Child mass: " << (compositeball->getBalls()[i]->mass()) << ", child position: (" << compositeball->getBalls()[i]->position().x() << "," << compositeball->getBalls()[i]->position().y() << ")" << std::endl;
                std::cout << "Relative position: (" << (compositeball->getBalls()[i]->position() - position).x() << ", " << (compositeball->getBalls()[i]->position() - position).y() << ")" << std::endl;

                //for each component ball
                QVector2D componentBallVelocity = preCollisionVelocity + sqrt(energyPerBall/(compositeball->getBalls()[i]->mass()))*((compositeball->getBalls()[i]->position() - position) - pointOfCollision).normalized();
                compositeball->getBalls()[i]->setVelocity(componentBallVelocity);
            }
        }
        else{
            if((b.position().x()<b.radius() && b.velocity().x()<0) || (b.position().x()>t.width()-b.radius() && b.velocity().x()>0))
            {
                b.changeVelocity(QVector2D(-b.velocity().x()*2, 0));
            }
            if((b.position().y()<b.radius() && b.velocity().y()<0) || (b.position().y()>t.height()-b.radius() && b.velocity().y()>0))
            {
                b.changeVelocity(QVector2D(0,-b.velocity().y()*2));
            }
        }
    }
}
