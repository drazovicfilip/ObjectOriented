#include "stagetwoball.h"

StageTwoBall::StageTwoBall()
{

}

void StageTwoBall::draw(QPainter &p)
{
    p.setPen(Qt::green);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
