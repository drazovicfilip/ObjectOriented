#include "ball.h"

#include <cmath>

Ball::Ball(Coordinate coordinate)
    : m_coordinate(coordinate)
    , m_radius(10)
    , m_xVelocity(0)
    , m_yVelocity(0)
{}

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
