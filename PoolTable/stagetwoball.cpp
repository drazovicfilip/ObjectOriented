#include "stagetwoball.h"
#include <QMouseEvent>
#include <iostream>

StageTwoBall::StageTwoBall()
{}

void StageTwoBall::draw(QPainter &p)
{

    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
