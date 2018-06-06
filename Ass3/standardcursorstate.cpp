#include "standardcursorstate.h"

StandardCursorState::StandardCursorState()
{

}

void StandardCursorState::draw(QPainter &p, QVector2D mousePos, Ball* m_ball){
    p.drawLine(mousePos.toPointF(),m_ball->position().toPointF());
}
