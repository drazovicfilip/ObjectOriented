#include "stageonetable.h"

void StageOneTable::draw(QPainter &p){
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawRect(0,0,m_width,m_height);
}
