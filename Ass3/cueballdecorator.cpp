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
    newball->setStates(m_states);
    return newball;
}

void CueBallDecorator::draw(QPainter &p)
{
    m_ball->draw(p);
    m_states.front()->draw(p, mousePos, this, clicked);
}

void CueBallDecorator::mousePressed(QMouseEvent *event)
{
    m_states.front()->processClickEvent(event, &mousePos, this, &clicked);
}

void CueBallDecorator::mouseMoved(QMouseEvent *event)
{
    mousePos = QVector2D(event->pos());
    if (clicked)
        m_states.front()->processMoveEvent(event, &mousePos, this);
}

void CueBallDecorator::mouseReleased(QMouseEvent *event)
{
    if(clicked)
    {
        clicked = false;
        m_states.front()->processReleaseEvent(event, &mousePos, m_ball);
    }
}

void CueBallDecorator::enterPressed(QKeyEvent* event){
    std::rotate(m_states.begin(), m_states.end()-1, m_states.end());
}
