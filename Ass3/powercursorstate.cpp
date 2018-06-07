#include "powercursorstate.h"

PowerCursorState::PowerCursorState()
{

}

void PowerCursorState::draw(QPainter &p, QVector2D mousePos, BallDecorator* dec, bool clicked){
    p.setBrush(Qt::blue);
    p.drawEllipse(mousePos.toPointF(), 15, 15);
    p.setBrush(Qt::red);
    p.drawEllipse(mousePos.toPointF(), 10, 10);
    p.setBrush(Qt::green);
    p.drawEllipse(mousePos.toPointF(),5, 5);
}
