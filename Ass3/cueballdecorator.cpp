#include "cueballdecorator.h"
CueBallDecorator::CueBallDecorator(Ball *b, Dialog *parent)
    :BallDecorator(b),clicked(false),m_parent(parent),mousePos(QVector2D(0,0))
{
    //connect dialog signals to cueball slots so that this class is notified when the mouse is used
    connect(parent,&Dialog::mousePressed,this,&CueBallDecorator::mousePressed);
    connect(parent,&Dialog::mouseMoved,this,&CueBallDecorator::mouseMoved);
    connect(parent,&Dialog::mouseReleased,this,&CueBallDecorator::mouseReleased);
    connect(parent,&Dialog::enterPressed,this,&CueBallDecorator::enterPressed);
}

CueBallDecorator* CueBallDecorator::clone(){
    CueBallDecorator* newball = new CueBallDecorator(this->ball()->clone(), m_parent);
    newball->setVelocity(QVector2D(0,0));
    return newball;
}

void CueBallDecorator::draw(QPainter &p)
{
    m_ball->draw(p);
    if(clicked)
        m_currentState->draw(p, mousePos, m_ball);
}

void CueBallDecorator::mousePressed(QMouseEvent *event)
{
    if(velocity().lengthSquared()<0.001 && (QVector2D(event->pos())-position()).length() < radius())
    {
        clicked = true;
        mousePos = QVector2D(event->pos());
    }
}

void CueBallDecorator::mouseMoved(QMouseEvent *event)
{
    if(clicked)
    {
        mousePos = QVector2D(event->pos());
    }

}

void CueBallDecorator::mouseReleased(QMouseEvent *event)
{
    if(clicked)
    {
        clicked = false;
        setVelocity(4*(m_ball->position()-mousePos));
    }
}

void CueBallDecorator::enterPressed(QKeyEvent* event){
    std::swap<CursorState *> (m_currentState, m_passiveState);
}
