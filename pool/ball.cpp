#include "ball.h"

#include <cmath>
#include <string>

// Default constructor
Ball::Ball(Coordinate coordinate)
    : m_coordinate(coordinate)
    , m_radius(10)
    , m_xVelocity(0)
    , m_yVelocity(0)
    , m_color(new std::string("#000000"))
    , m_type(stripe)
{}

// Standard constructor
Ball::Ball(Coordinate coordinate, std::string color, BallType type)
    : m_coordinate(coordinate)
    , m_radius(10)
    , m_xVelocity(1)
    , m_yVelocity(1)
    , m_color(new std::string(color))
    , m_type(type)
{}

Ball::~Ball(){
    delete m_color;
}

void Ball::render(QPainter &painter, unsigned int time){

    painter.setPen ( Qt::black );
    painter.setBrush( QBrush( Qt::yellow ) );
    painter.drawEllipse(m_coordinate.getQtRenderingXCoordinate() - (int) m_radius,
        m_coordinate.getQtRenderingYCoordinate() -(int) m_radius,
        m_radius * 2,
        m_radius * 2);

}

bool Ball::isCollision(){
    return false;
}
