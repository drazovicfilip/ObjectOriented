#include "ball.h"

#include <cmath>
#include <string>

// Default constructor
Ball::Ball(Coordinate coordinate)
    : m_coordinate(coordinate)
    , m_radius(20)
    , m_mass(1)
    , m_xVelocity(3)
    , m_yVelocity(3)
    , m_color(new std::string("#000000"))
{}

// Standard constructor
Ball::Ball(Coordinate coordinate, std::string color, int mass, int radius, double xVelocity, double yVelocity)
    : m_coordinate(coordinate)
    , m_mass(mass)
    , m_color(new std::string(color))
    , m_radius(radius)
    , m_xVelocity(xVelocity)
    , m_yVelocity(yVelocity)
{}


Ball::~Ball(){
    delete m_color;
}

void Ball::render(QPainter &painter, unsigned int time){

    // Account for friction (very approximated calculations)
    //m_xVelocity = 0.98*m_xVelocity;
    //m_yVelocity = 0.98*m_yVelocity;
    m_coordinate.changeInXCoordinate(m_xVelocity);
    m_coordinate.changeInYCoordinate(m_yVelocity);

    // Draw the ball for the current frame
    painter.setPen (Qt::black);
    painter.setBrush(QBrush(QColor(QString::fromStdString(*m_color))));
    painter.drawEllipse(m_coordinate.getQtRenderingXCoordinate() - m_radius,
        m_coordinate.getQtRenderingYCoordinate() - m_radius,
        m_radius * 2,
        m_radius * 2);

}
