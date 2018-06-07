#ifndef CUEBALLDECORATOR_H
#define CUEBALLDECORATOR_H
#include "balldecorator.h"
#include "dialog.h"
#include "cursorstate.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

/**
 * @brief The CueBallDecorator class is the decorator that turns a ball into a cue ball
 */
class CueBallDecorator : public BallDecorator, public QObject
{
    //Q_OBJECT
public:
    /**
     * @brief CueBallDecorator decorates a ball to be used as a cue ball
     * @param b is the ball to be decorated
     * @param parent is the parent Dialog, this is used to connect to the signals it emits
     */
    CueBallDecorator(Ball * b, Dialog * parent, PoolGame* game);
    CueBallDecorator* clone();
    void setDefaultState(CursorState *defaultState){ m_states.insert(m_states.begin(), defaultState); }
    void setPassiveState(CursorState *passiveState){ m_states.push_back(passiveState); }
    void setStates(std::vector<CursorState*> states){ m_states = states; }
    void draw(QPainter &p);
    void setGame(PoolGame* game){
        for (CursorState *state : m_states){
            state->setGame(game);
        }
    }

public slots:
    void mousePressed(QMouseEvent * event);
    void mouseMoved(QMouseEvent * event);
    void mouseReleased(QMouseEvent * event);
    void enterPressed(QKeyEvent *event);

private:
    QVector2D endpoint;
    Dialog* m_parent;
    PoolGame* m_game;
    QVector2D mousePos;
    CursorState *m_currentState;
    CursorState *m_passiveState;
    std::vector<CursorState*> m_states;
    bool clicked;
};

#endif // CUEBALLDECORATOR_H
