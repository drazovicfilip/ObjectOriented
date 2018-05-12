#include "stagetwoball.h"

StageTwoBall::StageTwoBall()
    : m_isCue(false)
{

}

void StageTwoBall::draw(QPainter &p)
{
    if (isCue())
    {
        p.setPen(Qt::green);
    }
    else
    {
        p.setPen(Qt::black);
    }

    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
