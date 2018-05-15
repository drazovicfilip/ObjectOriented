#include "compositeball.h"
#include <iostream>
#include "float.h"

CompositeBall::CompositeBall()
    : m_strength(FLT_MAX)
{}

void CompositeBall::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
