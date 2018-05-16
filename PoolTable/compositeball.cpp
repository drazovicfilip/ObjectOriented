#include "compositeball.h"
#include <iostream>
#include "float.h"

CompositeBall::CompositeBall()
    : m_hasParent(false)
{}

CompositeBall::CompositeBall(bool hasParent)
    : m_hasParent(hasParent)
{}

void CompositeBall::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);

    // Draw each of the children as well
    std::vector<Ball*> b = getBalls();
    for (int i = 0; i < b.size() ; i++)
    {
        b[i]->draw(p);
    }

}
