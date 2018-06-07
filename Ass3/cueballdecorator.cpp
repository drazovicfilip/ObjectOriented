#include "cueballdecorator.h"
CueBallDecorator::CueBallDecorator(Ball *b, Dialog *parent, PoolGame* game)
    :BallDecorator(b),clicked(false),m_parent(parent),mousePos(QVector2D(0,0)),m_game(game)
{
    //connect dialog signals to cueball slots so that this class is notified when the mouse is used
    connect(parent,&Dialog::mousePressed,this,&CueBallDecorator::mousePressed);
    connect(parent,&Dialog::mouseMoved,this,&CueBallDecorator::mouseMoved);
    connect(parent,&Dialog::mouseReleased,this,&CueBallDecorator::mouseReleased);
    connect(parent,&Dialog::enterPressed,this,&CueBallDecorator::enterPressed);
}

CueBallDecorator* CueBallDecorator::clone(){
    CueBallDecorator* newball = new CueBallDecorator(this->ball()->clone(), m_parent, m_game);
    newball->setVelocity(QVector2D(0,0));
    m_currentState->setGame(m_game);
    newball->setDefaultState(m_currentState);
    m_passiveState->setGame(m_game);
    newball->setPassiveState(m_passiveState);
    return newball;
}

void CueBallDecorator::draw(QPainter &p)
{
    m_ball->draw(p);
    m_currentState->draw(p, mousePos, this, clicked);
}

void CueBallDecorator::mousePressed(QMouseEvent *event)
{
    m_currentState->processClickEvent(event, &mousePos, this, &clicked);
}

void CueBallDecorator::mouseMoved(QMouseEvent *event)
{
    mousePos = QVector2D(event->pos());
}

void CueBallDecorator::mouseReleased(QMouseEvent *event)
{
    if(clicked)
    {
        clicked = false;
        m_currentState->processReleaseEvent(event, &mousePos, m_ball);
    }
}

void CueBallDecorator::enterPressed(QKeyEvent* event){
    std::swap<CursorState *> (m_currentState, m_passiveState);
}
