#include "simpleball.h"
#include "float.h"

SimpleBall::SimpleBall()
    : m_strength(FLT_MAX)
{}

void SimpleBall::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
