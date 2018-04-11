#include "dialog.h"
#include "ui_dialog.h"
#include <QTextStream>
#include <QRect>

#define simtime 2
#define frametime 8

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{

    PoolBuilder builder;
    Director director(&builder);
    pool = director.construct();

    ui->setupUi(this);
    this->resize(director.tablewidthJSON(), director.tableheightJSON());

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(frametime);

    QTimer *timersim = new QTimer(this);
    connect(timersim, SIGNAL(timeout()), this, SLOT(simulate()));
    timersim->start(simtime);
}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::simulate(){
    std::vector<Ball *> balls = pool.getBalls();
    for(Ball * currentball : balls){
        isCollisionBallBall(currentball, balls);
        isCollisionBallTable(currentball, pool.getTable());
        currentball->changeXVelocity(-9.81*pool.getTable()->getFriction()*(double(simtime)/double(1000))*currentball->getXVelocity());
        currentball->changeYVelocity(-9.81*pool.getTable()->getFriction()*(double(simtime)/double(1000))*currentball->getYVelocity());
        currentball->changeinXCoordinate(currentball->getXVelocity()*(double(simtime)/double(1000)));
        currentball->changeinYCoordinate(currentball->getYVelocity()*(double(simtime)/double(1000)));
    }
}

void Dialog::paintEvent(QPaintEvent *event){

    // Draw a simple table
    QPainter painter(this);

    pool.getTable()->render(painter);

    std::vector<Ball *> balls = pool.getBalls();
    for(Ball * currentball : balls){

        //isCollisionBallBall(currentball, balls);
        //isCollisionBallTable(currentball, pool.getTable());
        currentball->render(painter);

        //delete currentball;
    }

}

void Dialog::nextFrame(){
    update();
}

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

void Dialog::isCollisionBallBall(Ball* currentball, std::vector<Ball *> ballsarray){

    for (int i = distance(ballsarray.begin(), std::find(ballsarray.begin(), ballsarray.end(), currentball)) + 1; i < (int)ballsarray.size(); i++){
    //for (int i = 0; i < ballsarray.size(); i++){

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

            currentball->changeXVelocity(deltaVA[0]);
            currentball->changeYVelocity(deltaVA[1]);

            otherball->changeXVelocity(deltaVB[0]);
            otherball->changeYVelocity(deltaVB[1]);

        }
    }

}





