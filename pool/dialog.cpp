#include "dialog.h"
#include "ui_dialog.h"
#include <QTextStream>
#include <QRect>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , table(1000, 600, 20, 50)
{

    // Create 6 balls
    balls.push_back(new Ball(Coordinate(fwidth/3, fheight/2, fheight, fwidth), "blue", 1, 20, 3, 0));
    balls.push_back(new Ball(Coordinate(fwidth/5, fheight-140, fheight, fwidth), "green", 2, 20, 5, 3));
    balls.push_back(new Ball(Coordinate(fwidth/3, fheight-200, fheight, fwidth), "red", 3, 20, 5, 1));
    balls.push_back(new Ball(Coordinate(fwidth/7, fheight/3, fheight, fwidth), "white", 4, 20, -1, 2));
    balls.push_back(new Ball(Coordinate(fwidth/5, fheight/4, fheight, fwidth), "black", 5, 20, -4, 3));
    balls.push_back(new Ball(Coordinate(fwidth/2, fheight/6, fheight, fwidth), "pink", 6, 20, 1, -5));

    ui->setupUi(this);
    this->resize(fwidth,fheight);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(8);
}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event){

    // Draw a simple table
    QPainter painter(this);

    table.render(painter, m_counter);

    for(Ball * currentball : balls){

        isCollisionBallBall(currentball, balls);

        isCollisionBallTable(currentball);
        currentball->render(painter,m_counter);

        //delete currentball;
    }
}

void Dialog::nextFrame(){
    update();
}

void Dialog::isCollisionBallTable(Ball* currentball){

        // Bouncing off either side
        if ((currentball->getCoordinate().getQtRenderingXCoordinate() >=
             (currentball->getCoordinate().getFrameWidth() - table.getSpace() - table.getThickness()/2 - currentball->getRadius())) || (currentball->getCoordinate().getQtRenderingXCoordinate() <= currentball->getRadius() + table.getThickness()/2 + table.getSpace())){
            currentball->flipXVelocity();
        }

        // Bouncing off top or bottom
        if ((currentball->getCoordinate().getQtRenderingYCoordinate() >=
             (currentball->getCoordinate().getFrameHeight() - table.getSpace() - table.getThickness()/2 - currentball->getRadius())) || (currentball->getCoordinate().getQtRenderingYCoordinate() <= currentball->getRadius() + table.getThickness()/2 + table.getSpace())){
            currentball->flipYVelocity();
        }
}

void Dialog::isCollisionBallBall(Ball* currentball, std::vector<Ball *> ballsarray){

    for (int i = distance(ballsarray.begin(), std::find(ballsarray.begin(), ballsarray.end(), currentball)) + 1; i < ballsarray.size(); i++){
    //for (int i = 0; i < ballsarray.size(); i++){

        Ball* otherball = ballsarray[i];

        int centreAx = currentball->getCoordinate().getQtRenderingXCoordinate();
        int centreAy = currentball->getCoordinate().getYCoordinate();
        int centreBx = otherball->getCoordinate().getQtRenderingXCoordinate();
        int centreBy = otherball->getCoordinate().getYCoordinate();
        int radA = currentball->getRadius();
        int radB = otherball->getRadius();

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
            double vA = QVector2D::dotProduct(collisionVector, velA);
            double vB = QVector2D::dotProduct(collisionVector, velB);
            //the balls are moving away from each other so do nothing
            if ((vA <= 0 && vB >= 0)) {
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
            QVector2D deltaVA = mR * (vB - root) * collisionVector;
            QVector2D deltaVB = (root - vB) * collisionVector;

            /*
            out << "Centre A: " << centreAx << ", " << centreAy << endl;
            out << "Centre B: " << centreBx << ", " << centreBy << endl;
            out << "Velocity A: " << currentball->getXVelocity() << ", " << currentball->getYVelocity() << endl;
            out << "Velocity B: " << otherball->getXVelocity() << ", " << otherball->getYVelocity() << endl;
            out << "Mass A: " << massA << endl;
            out << "Mass B: " << massB << endl;

            */

            out << "Delta A: " << deltaVA[0] << ", " << deltaVA[1] << endl;
            out << "Delta B: " << deltaVA[0] << ", " << deltaVA[1] << endl;
            out << "- - - - -" << endl;

            currentball->changeXVelocity((int)deltaVA[0]);
            currentball->changeYVelocity((int)deltaVA[1]);

            otherball->changeXVelocity((int)deltaVB[0]);
            otherball->changeYVelocity((int)deltaVB[1]);


        }
    }





    }



