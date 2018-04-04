#include "ball.h"

#include <cmath>
#include <string>

#define redball "#ff5050"

// Default constructor
Ball::Ball(Coordinate coordinate)
    : m_coordinate(coordinate)
    , m_radius(20)
    , m_xVelocity(3)
    , m_yVelocity(3)
    , m_color(new std::string("#000000"))
    , m_type(stripe)
{}

Ball::Ball(Coordinate coordinate, int xVelocity, int yVelocity)
    : m_coordinate(coordinate)
    , m_radius(20)
    , m_xVelocity(xVelocity)
    , m_yVelocity(yVelocity)
    , m_color(new std::string("#000000"))
    , m_type(stripe)
{}

// Standard constructor
Ball::Ball(Coordinate coordinate, std::string color, BallType type)
    : m_coordinate(coordinate)
    , m_radius(10)
    , m_xVelocity(10)
    , m_yVelocity(0)
    , m_color(new std::string(color))
    , m_type(type)
{}

Ball::~Ball(){
    delete m_color;
}

void Ball::render(QPainter &painter, unsigned int time){

    // Check for collision with the sides of the table
    collisionLocation collision = Ball::isCollision();
    switch(collision){
        case(vertical):
            m_yVelocity *= -1;
            break;
        case(horizontal):
            m_xVelocity *= -1;
            break;
    }

    // Draw the ball for the current frame
    painter.setPen ( Qt::black );
    painter.setBrush(QBrush(redball));
    painter.drawEllipse(m_coordinate.getQtRenderingXCoordinate() - (int) m_radius,
        m_coordinate.getQtRenderingYCoordinate() -(int) m_radius,
        m_radius * 2,
        m_radius * 2);

    // Account for friction (very approximated calculations)
    //m_xVelocity = 0.98*m_xVelocity;
    //m_yVelocity = 0.98*m_yVelocity;
    m_coordinate.changeInXCoordinate(m_xVelocity);
    m_coordinate.changeInYCoordinate(m_yVelocity);

}

collisionLocation Ball::isCollision(){

    if ((m_coordinate.getQtRenderingXCoordinate() >
         (signed int) (m_coordinate.getFrameWidth() - outsidedist - tablethickness - (signed int) m_radius)) || (m_coordinate.getQtRenderingXCoordinate() < (signed int) m_radius + tablethickness + outsidedist)){
        return horizontal;
    }

    if ((m_coordinate.getQtRenderingYCoordinate() >
         (signed int) (m_coordinate.getFrameHeight() - outsidedist - tablethickness - (signed int) m_radius)) || (m_coordinate.getQtRenderingYCoordinate() < (signed int) m_radius + tablethickness + outsidedist)){
        return vertical;
    }

    return none;
}
