#ifndef POOLGAME_H
#define POOLGAME_H

#include <vector>
#include <QPainter>
#include <QSize>

#include "table.h"
#include "ball.h"
#include "memento.h"
#include "originator.h"

#include "changeinpoolgame.h"

/**
 * @brief The PoolGame class runs the pool game, it is in charge of the physics of the pool game as well as
 * drawing the game
 */
class PoolGame
{
public:
    /**
     * @brief PoolGame constructor
     * @param m_table a pointer to a Table object, Poolgame takes ownership of this pointer
     * @param balls a vector of pointers to balls, Poolgame takes ownership of all the contained pointers
     */
    PoolGame(Table * m_table,std::vector<Ball*> balls)
        :m_table(m_table),m_balls(balls)
    {
    }

    PoolGame()
        : m_table()
        , m_balls()
    {}

    ~PoolGame();

    std::vector<Ball*> copyBalls(std::vector<Ball*> balls);
    void saveBalls();
    void restoreBalls();
    void rockTable(int direction);

    /**
     * @brief simulate one timestep of the game
     * @param timeStep is the period of time that this timestep is simulating
     */
    void simulateTimeStep(float timeStep);

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
    void draw(QPainter &p);

    /**
     * @brief size
     * @return the size of the game
     */
    QSize size(){return QSize(m_table->width(),m_table->height());}

    void toggleBallVisibility();

    int ballsLength(){ return m_balls.size(); }
    void setCueBallStopped(int v){ cueballstopped = v; }
    void setStage(int v){ m_stage = v; }
    const int stage(){ return m_stage; }

private:
    /**
     * @brief collide two balls if they are in contact
     * @param b1
     * @param b2
     * @return the change in the pool game after the collision
     */
    ChangeInPoolGame collide(Ball *b1, Ball *b2);
    std::vector<Memento*> savedState;
    int m_stage;
    Originator originator;
    Table * m_table;
    int cueballstopped = 0;
    std::vector<Ball*> m_balls;
};

#endif // POOLGAME_H
