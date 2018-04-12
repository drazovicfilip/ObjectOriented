#include "dialog.h"
#include "ui_dialog.h"
#include <QTextStream>
#include <QRect>

/**
 * @brief The dialog class is the coordinator of the whole program.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * It will perform all physics calculations and call upon objects to render themselves.
 * It will also initialise the pool table using the director/builder design method.
 */

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    // Call upon the director to construct the pool game by using the builders and factories
    PoolBuilder builder;
    Director director(&builder);
    pool = director.construct();

    // Resize the UI window to be the same size as given in the JSON file
    ui->setupUi(this);
    this->resize(director.tablewidthJSON(), director.tableheightJSON());

    // Timer for the framerate. This will call the nextFrame() function (rendering) every time the timer ticks
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(frametime);

    // Timer for the simulation. This will call the simulate() function (physics) every time the timer ticks
    QTimer *timersim = new QTimer(this);
    connect(timersim, SIGNAL(timeout()), this, SLOT(simulate()));
    timersim->start(simtime);
}

Dialog::~Dialog(){
    delete ui;
}

/**
 * @brief simulate will calculate all physics and update positions/velocities of balls
 *
 * This involves calculating friction, checking to see if a ball has collided with the table and checking
 * to see if a ball has collided with another ball
 * The simulation rate can be changed by altering the simtime variable
 */
void Dialog::simulate(){

    // Check physics for each ball on the table
    std::vector<Ball *> balls = pool.getBalls();
    for(Ball * currentball : balls){

        // Check for any collisions
        isCollisionBallBall(currentball, balls);
        isCollisionBallTable(currentball, pool.getTable());

        // Apply friction
        currentball->changeXVelocity(-9.81*pool.getTable()->getFriction()*(double(simtime)/double(1000))*currentball->getXVelocity());
        currentball->changeYVelocity(-9.81*pool.getTable()->getFriction()*(double(simtime)/double(1000))*currentball->getYVelocity());

        // Apply calculated velocity changes to the position so the render method can render correctly next time it is called
        currentball->changeinXCoordinate(currentball->getXVelocity()*(double(simtime)/double(1000)));
        currentball->changeinYCoordinate(currentball->getYVelocity()*(double(simtime)/double(1000)));
    }
}

/**
 * @brief paintEvent will render the game, and is called every time nextFrame() is called
 * @param event
 */
void Dialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    pool.render(painter);
}


/**
 * @brief nextFrame will render the next frame using each object's render method
 *
 * This will call the pool class' render method, which will use the render method of each ball and table.
 * The rendering rate (framerate) can be changed by altering the frametime variable
 */
void Dialog::nextFrame(){
    update();
}

/**
 * @brief isCollisionBallTable will check whether a given ball has collided with the table. If it has, it will reverse its velocity
 * @param currentball
 * @param table
 */
void Dialog::isCollisionBallTable(Ball* currentball, Table* table){

        // Bouncing off either side
        if ((currentball->getCoordinate().getQtRenderingXCoordinate() >=
             (currentball->getCoordinate().getFrameWidth() - table->getSpace() - table->getThickness()/2 - currentball->getRadius())) || (currentball->getCoordinate().getQtRenderingXCoordinate() <= currentball->getRadius() + table->getThickness()/2 + table->getSpace())){

            currentball->flipXVelocity();

        }

        // Bouncing off top or bottom
        if ((currentball->getCoordinate().getQtRenderingYCoordinate() >=
             (currentball->getCoordinate().getFrameHeight() - table->getSpace() - table->getThickness()/2 - currentball->getRadius())) || (currentball->getCoordinate().getQtRenderingYCoordinate() <= currentball->getRadius() + table->getThickness()/2 + table->getSpace())){

            currentball->flipYVelocity();

        }
}

/**
 * @brief isCollisionBallBall will check if a ball is colliding with any other ball. If it has, it'll calculate the updated velocities for each ball.
 * @param currentball1
 * @param balls
 */
void Dialog::isCollisionBallBall(Ball* currentball, std::vector<Ball *> ballsarray){

    // It is incorrect to check every single other ball, as it will result in double-ups.
    // Every pair of balls should only be checked once
    for (int i = distance(ballsarray.begin(), std::find(ballsarray.begin(), ballsarray.end(), currentball)) + 1; i < (int)ballsarray.size(); i++){

        Ball* otherball = ballsarray[i];

        float centreAx = currentball->getCoordinate().getQtRenderingXCoordinate();
        float centreAy = currentball->getCoordinate().getYCoordinate();
        float centreBx = otherball->getCoordinate().getQtRenderingXCoordinate();
        float centreBy = otherball->getCoordinate().getYCoordinate();
        float radA = currentball->getRadius();
        float radB = otherball->getRadius();

        // If the distance between the ball's centres is less than the sum of their radii

        if (sqrt(pow((centreBy-centreAy), 2) + pow((centreAx-centreBx), 2)) <= (radA + radB)){

            //Properties of two colliding balls,
            //ball A
            QVector2D posA(centreAx, centreAy);
            QVector2D velA(currentball->getXVelocity(), currentball->getYVelocity());
            float massA = currentball->getMass();
            //and ball B
            QVector2D posB(centreBx, centreBy);
            QVector2D velB(otherball->getXVelocity(), otherball->getYVelocity());

            float massB = otherball->getMass();

            //calculate their mass ratio
            float mR = massB / massA;

            //calculate the axis of collision
            QVector2D collisionVector = posB - posA;
            collisionVector.normalize();

            //the proportion of each balls velocity along the axis of collision
            float vA = QVector2D::dotProduct(collisionVector, velA);
            float vB = QVector2D::dotProduct(collisionVector, velB);


            //the balls are moving away from each other so do nothing
            if ((vA <= 0 && vB >= 0)) {
                return;
            }

            //The velocity of each ball after a collision can be found by solving the quadratic equation
            //given by equating momentum and energy before and after the collision and finding the velocities
            //that satisfy this
            //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
            //first we find the discriminant
            float a = -(mR + 1);
            float b = 2 * (mR * vB + vA);
            float c = -((mR - 1) * vB * vB + 2 * vA * vB);
            float discriminant = sqrt(b * b - 4 * a * c);
            float root = (-b + discriminant)/(2 * a);
            //only one of the roots is the solution, the other pertains to the current velocities
            if (root - vB < 0.01) {
                root = (-b - discriminant)/(2 * a);
            }


            //The resulting changes in velocity for ball A and B
            QVector2D deltaVA = mR * (vB - root) * collisionVector;
            QVector2D deltaVB = (root - vB) * collisionVector;

            // Update the ball's velocities using the calculations made. Their positions will be updated outside this function
            currentball->changeXVelocity(deltaVA[0]);
            currentball->changeYVelocity(deltaVA[1]);
            otherball->changeXVelocity(deltaVB[0]);
            otherball->changeYVelocity(deltaVB[1]);

        }
    }

}





