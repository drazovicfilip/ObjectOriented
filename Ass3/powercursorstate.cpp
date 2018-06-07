#include "powercursorstate.h"
#include "poolgame.h"

PowerCursorState::PowerCursorState()
    : CursorState()
    , frame(0)
    , framedirection(1)
{
    colours.push_back(QColor(Qt::blue));
    colours.push_back(QColor(Qt::red));
    colours.push_back(QColor(Qt::magenta));

}

void PowerCursorState::draw(QPainter &p, QVector2D mousePos, BallDecorator* dec, bool clicked){

    if (clicked){
        QPen pen;
        pen.setWidth(3);
        pen.setCapStyle(Qt::RoundCap);
        pen.setBrush(Qt::white);
        p.setPen(pen);
        p.drawLine(dec->position().x(), dec->position().y(), (frame*mousePos.x() + (15-frame)*dec->position().x())/15, (frame*mousePos.y() + (15-frame)*dec->position().y())/15);
        pen.setBrush(colours.back());
        p.setPen(pen);
        p.drawLine(mousePos.x(), mousePos.y(), (frame*mousePos.x() + (15-frame)*dec->position().x())/15, (frame*mousePos.y() + (15-frame)*dec->position().y())/15);

        if (frame == 15){
            setFrameDirection(0);
        }
        if (frame == 0){
            setFrameDirection(1);
            std::random_shuffle(colours.begin(), colours.end());
        }
        if (getFrameDirection()){
            setFrame(getFrame() + 1);
        }
        else{
            setFrame(getFrame() - 1);
        }
    }
}

void PowerCursorState::processClickEvent(QMouseEvent *event, QVector2D *mousePos, BallDecorator *dec, bool *clicked){
    if(dec->velocity().lengthSquared()<0.001 && (QVector2D(event->pos())-dec->position()).length() < dec->radius())
    {
        *clicked = true;
        *mousePos = QVector2D(event->pos());
    }
}

void PowerCursorState::processReleaseEvent(QMouseEvent *event, QVector2D* mousePos, Ball* m_ball){
    m_ball->setVelocity(10*(m_ball->position()-*mousePos));
}


