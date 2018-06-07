#include "standardcursorstate.h"

StandardCursorState::StandardCursorState()
    :CursorState()
{}

void StandardCursorState::draw(QPainter &p, QVector2D mousePos, BallDecorator* dec, bool clicked){
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    if (clicked)
        p.drawLine(mousePos.toPointF(), dec->position().toPointF());
}

void StandardCursorState::processClickEvent(QMouseEvent *event, QVector2D* mousePos, BallDecorator* dec, bool* clicked){
    if(dec->velocity().lengthSquared()<0.001 && (QVector2D(event->pos())-dec->position()).length() < dec->radius())
    {
        *clicked = true;
        *mousePos = QVector2D(event->pos());
    }
}

void StandardCursorState::processReleaseEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball){
    m_ball->setVelocity(2*(m_ball->position()-*mousePos));
}
