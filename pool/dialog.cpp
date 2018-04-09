#include "dialog.h"
#include "ui_dialog.h"
#include <QTextStream>
#include <QRect>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{

    PoolBuilder builder;
    Director director(&builder);
    pool = director.construct();

    // Create 6 balls
    //balls.push_back(new Ball(Coordinate(fwidth/5, fheight/2, fheight, fwidth), "green", 1, 20, -3, -3));
    //balls.push_back(new Ball(Coordinate(fwidth/5, fheight/4, fheight, fwidth), "green", 1, 20, 3, 3));

    ui->setupUi(this);
    this->resize(fwidth,fheight);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(50);
}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event){

    // To make the compiler shush about event not being used
    event = 0;

    // Draw a simple table
    QPainter painter(this);

    pool.getTable()->render(painter);

    std::vector<Ball *> balls = pool.getBalls();

    for(Ball * currentball : balls){

        isCollisionBallBall(currentball, balls);
        isCollisionBallTable(currentball, pool.getTable());
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

            // If the ball is still not in the table
            //if (currentball->getCoordinate().getQtRenderingXCoordinate() > currentball->getCoordinate().getFrameWidth() - table->getThickness() - table->getSpace() || currentball->getCoordinate().getQtRenderingXCoordinate() > table->getSpace() + table->getThickness()/2){
            //    currentball->flipXVelocity();
            //}

            currentball->flipXVelocity();
            QTextStream out(stdout);
            out << "Velocity is now " << currentball->getXVelocity() << ", " << currentball->getYVelocity() << endl;
            out << "Velocity is now " << currentball->getXVelocity() << ", " << currentball->getYVelocity() << endl;


        }

        // Bouncing off top or bottom
        if ((currentball->getCoordinate().getQtRenderingYCoordinate() >=
             (currentball->getCoordinate().getFrameHeight() - table->getSpace() - table->getThickness()/2 - currentball->getRadius())) || (currentball->getCoordinate().getQtRenderingYCoordinate() <= currentball->getRadius() + table->getThickness()/2 + table->getSpace())){

            // If the ball is still not in the table
            //if (currentball->getCoordinate().getYCoordinate() > currentball->getCoordinate().getFrameHeight() - table->getThickness() - table->getSpace() || currentball->getCoordinate().getYCoordinate() > table->getSpace() + table->getThickness()/2){
            //    currentball->flipYVelocity();
            //}

            currentball->flipYVelocity();
            QTextStream out(stdout);
            out << "Velocity is now " << currentball->getXVelocity() << ", " << currentball->getYVelocity() << endl;

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

            QTextStream out(stdout);
            out << "Ball " << currentball->getMass() << " | C: "<< centreAx << ", " << centreAy << " | V: "<< velA[0] << ", " << velA[1] << endl;
            out << "Ball " << otherball->getMass() << " | C: "<< centreBx << ", " << centreBy << " | V: "<< velB[0] << ", " << velB[1] << endl;

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


            out << "Centre A: " << centreAx << ", " << centreAy << endl;
            out << "Centre B: " << centreBx << ", " << centreBy << endl;
            out << "Velocity A: " << currentball->getXVelocity() << ", " << currentball->getYVelocity() << endl;
            out << "Velocity B: " << otherball->getXVelocity() << ", " << otherball->getYVelocity() << endl;
            out << "Mass A: " << massA << endl;
            out << "Mass B: " << massB << endl;



            out << "Delta A: " << deltaVA[0] << ", " << deltaVA[1] << endl;
            out << "Delta B: " << deltaVB[0] << ", " << deltaVB[1] << endl;
            out << "V A: " << vA << endl;
            out << "V B: " << vB << endl;
            out << "- - - - -" << endl;

            currentball->changeXVelocity(deltaVA[0]);
            currentball->changeYVelocity(deltaVA[1]);

            otherball->changeXVelocity(deltaVB[0]);
            otherball->changeYVelocity(deltaVB[1]);

        }
    }

}





