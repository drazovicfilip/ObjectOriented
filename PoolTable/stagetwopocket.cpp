#include "stagetwopocket.h"

StageTwoPocket::StageTwoPocket()
{}

void StageTwoPocket::draw(QPainter &p){
    p.setPen(Qt::black);
    p.setBrush(Qt::black);
    p.drawEllipse(m_position.toPointF(), m_radius, m_radius);
}
