#include "balldecorator.h"

BallDecorator::BallDecorator(Ball* ball)
    : m_ball(ball)
{}

void BallDecorator::draw(QPainter &p)
{
    m_ball->draw(p);
}

void BallDecorator::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        std::cout << "decorator press" << std::endl;
    }

}
void BallDecorator::mouseMoveEvent(QMouseEvent *event)
{
    std::cout << "decorator move" << std::endl;
}
void BallDecorator::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "decorator release" << std::endl;
}

