#include "grabcursorstate.h"
#include "math.h"

GrabCursorState::GrabCursorState()
    : CursorState()
    , frame(0)
    , framedirection(1)
{}

void GrabCursorState::processClickEvent(QMouseEvent *event, QVector2D *mousePos, BallDecorator *dec, bool *clicked){
    if (sqrt(pow(mousePos->x() - dec->position().x(), 2) + pow(mousePos->y() - dec->position().y(), 2)) <= dec->radius()){
        *clicked = true;
    }
}

void GrabCursorState::processReleaseEvent(QMouseEvent *event, QVector2D *mousePos, Ball *m_ball){

}

void GrabCursorState::processMoveEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball){
    m_ball->setPosition(QVector2D(mousePos->x(),mousePos->y()));
}


void GrabCursorState::draw(QPainter &p, QVector2D mousePos, BallDecorator *dec, bool clicked){
    if (sqrt(pow(mousePos.x() - dec->position().x(), 2) + pow(mousePos.y() - dec->position().y(), 2)) <= dec->radius()){
       if (clicked){
           QApplication::setOverrideCursor(Qt::ClosedHandCursor);
       }
       else{
           QApplication::setOverrideCursor(Qt::OpenHandCursor);
       }
       QPen pen;
       pen.setColor(Qt::black);
       QBrush brush;
       brush.setColor(nullptr);
       p.setPen(pen);
       p.setBrush(brush);
       p.drawEllipse(dec->position().toPointF(), dec->radius() + frame, dec->radius() + frame);
       if (frame == 15){
           setFrameDirection(0);
       }
       if (frame == 0){
           setFrameDirection(1);
       }
       if (getFrameDirection()){
           setFrame(getFrame() + 1);
       }
       else{
           setFrame(getFrame() - 1);
       }
    }
    else{
        QApplication::setOverrideCursor(Qt::OpenHandCursor);
    }

}

