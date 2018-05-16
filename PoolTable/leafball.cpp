#include "leafball.h"
#include <iostream>
#include "float.h"

LeafBall::LeafBall()
    : m_hasParent(false)
{}

void LeafBall::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);

}
