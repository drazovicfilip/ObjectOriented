#include "stageoneball.h"

StageOneBall::StageOneBall()
{

}

void StageOneBall::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
