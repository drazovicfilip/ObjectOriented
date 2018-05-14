#include "balldecorator.h"
#include <math.h>

BallDecorator::BallDecorator(Ball* ball)
    : m_ball(ball)
    , mousePressed(false)
    , mouseReleased(true)
    , mousePosition(-1, -1)
{}

void BallDecorator::draw(QPainter &p)
{
    if (mousePressed && m_ball->velocity().x() == 0 && m_ball->velocity().y() == 0)
    {
        const double mouseX = mousePosition.x();
        const double mouseY = mousePosition.y();
        p.setPen(QPen(Qt::black, 4));
        p.drawLine(m_ball->position().x(), m_ball->position().y(), mouseX, mouseY);

        p.setPen(QPen(Qt::black, 2, Qt::DotLine));
        p.drawLine(m_ball->position().x(), m_ball->position().y(), m_ball->position().x() - ((mouseX) - m_ball->position().x()), m_ball->position().y() - ((mouseY) - m_ball->position().y()));

    }
    m_ball->draw(p);
}

void BallDecorator::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mousePosition = QVector2D(event->x(), event->y());
        mousePressed = true;
    }

}

void BallDecorator::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && mousePressed)
    {
        mousePosition = QVector2D(event->x(), event->y());
    }
}

void BallDecorator::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && mousePressed)
    {
        mousePosition = QVector2D(-1, -1);
        mousePressed = false;

        if (m_ball->velocity().x() == 0 && m_ball->velocity().y() == 0)
        {
             m_ball->setVelocity(QVector2D(-3*(event->x()-m_ball->position().x()), -3*(event->y()-m_ball->position().y())));
        }
    }

}

