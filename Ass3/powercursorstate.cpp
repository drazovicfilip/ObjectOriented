#include "powercursorstate.h"

PowerCursorState::PowerCursorState()
{

}

void PowerCursorState::draw(QPainter &p, QVector2D mousePos, Ball* m_ball){
    p.setPen(Qt::green);
    p.drawLine(mousePos.toPointF(),m_ball->position().toPointF());
}
