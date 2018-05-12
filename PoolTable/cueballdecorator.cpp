#include "cueballdecorator.h"

CueBallDecorator::CueBallDecorator(Ball* ball)
    : m_ball(ball)
{}

void CueBallDecorator::draw(QPainter &p)
{
    m_ball->draw(p);
    std::cout << "decorator drawing " << m_ball->radius() << std::endl;
}

void CueBallDecorator::mousePressEvent(QMouseEvent *event)
{
    std::cout << "decorator press" << std::endl;
}
void CueBallDecorator::mouseMoveEvent(QMouseEvent *event)
{
    std::cout << "decorator move" << std::endl;
}
void CueBallDecorator::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "decorator release" << std::endl;
}
