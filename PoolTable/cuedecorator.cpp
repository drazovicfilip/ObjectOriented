#include "cuedecorator.h"

CueDecorator::CueDecorator(Ball* ball)
    : m_ball(ball)
{}

void CueDecorator::draw(QPainter &p)
{
    ball->draw(QPainter &p);
    std::cout << "decorator drawing" << std::endl;
}

void mousePressEvent(QMouseEvent *event)
{
    std::cout << "decorator press" << std::endl;
}
void mouseMoveEvent(QMouseEvent *event)
{
    std::cout << "decorator move" << std::endl;
}
void mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "decorator release" << std::endl;
}
