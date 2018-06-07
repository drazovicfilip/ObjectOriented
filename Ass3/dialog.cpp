#include "dialog.h"

#include <QPainter>
#include <QSize>

constexpr float fps = 60;
constexpr float timeStep = 0.01;

Dialog::Dialog(QWidget *parent)
    :QDialog(parent),m_game(nullptr),m_framerateTimer(new QTimer()),m_timestepTimer(new QTimer())
{
    this->setMouseTracking(true);

}

void Dialog::start(PoolGame *game)
{
    m_game = game;
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer,SIGNAL(timeout()),this,SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/fps);
    m_timestepTimer->start(1000*timeStep);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    m_game->draw(p);
}

void Dialog::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Space){
        m_game->toggleBallVisibility();
    }

    if (event->key() == Qt::Key_R && m_game->stage() == 3){
        m_game->restoreBalls();
    }

    if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && m_game->stage() == 3){
        emit enterPressed(event);
    }
    if (event->key() == Qt::Key_Right){
        m_game->rockTable(0);
    }
    else if (event->key() == Qt::Key_Down){
        m_game->rockTable(1);
    }
    else if (event->key() == Qt::Key_Left){
        m_game->rockTable(2);
    }
    else if (event->key() == Qt::Key_Up){
        m_game->rockTable(3);
    }
}


void Dialog::mousePressEvent(QMouseEvent *event)
{
    emit mousePressed(event);
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}

void Dialog::makeBall(QVector2D position, size_t radius){
    std::cout << "make ball" << std::endl;
}


Dialog::~Dialog()
{
    delete m_game;
    delete m_framerateTimer;
    delete m_timestepTimer;
}

void Dialog::runSimulationStep()
{
    m_game->simulateTimeStep(timeStep);
}
