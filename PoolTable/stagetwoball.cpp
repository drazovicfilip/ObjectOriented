#include "stagetwoball.h"
#include <iostream>
#include "float.h"

StageTwoBall::StageTwoBall()
    : m_strength(FLT_MAX)
{}

void StageTwoBall::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
