#include "dialog.h"

#include <QPainter>
#include <QSize>
#include <QKeyEvent>

#include <iostream>

constexpr float fps = 60;
constexpr float timeStep = 0.01;

Dialog::Dialog(PoolGame *game, QWidget *parent)
    : QDialog(parent)
    , m_game(game)
    , m_framerateTimer(new QTimer())
    , m_timestepTimer(new QTimer())
    {
        this->setMinimumSize(m_game->size());
        this->resize(m_game->size());

        // Set the BallDecorator class to be a child of Dialog in order for it to be able to handle mouse events
        if (game->stage() == 2){
            game->linkQWidgetParentToCueBall(this);
    }

    connect(m_framerateTimer, SIGNAL(timeout()), this, SLOT(update()));
    connect(m_timestepTimer, SIGNAL(timeout()), this, SLOT(runSimulationStep()));
}

void Dialog::start(){
    m_framerateTimer->start(1000/fps);
    m_timestepTimer->start(1000*timeStep);
}

void Dialog::paintEvent(QPaintEvent *){
    QPainter p(this);
    m_game->draw(p);
}

void Dialog::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Space){
        m_game->toggleChildrenVisibility();
    }
}

Dialog::~Dialog(){
    delete m_game;
    delete m_framerateTimer;
    delete m_timestepTimer;
}

void Dialog::runSimulationStep(){
    m_game->simulateTimeStep(timeStep);
}
