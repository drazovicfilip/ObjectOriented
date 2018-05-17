#ifndef POOLGAME_H
#define POOLGAME_H

#include <vector>
#include <QPainter>
#include <QSize>

#include "table.h"
#include "ball.h"
#include "pocket.h"

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
    {}
    PoolGame(Table * m_table, std::vector<Ball*> balls, std::vector<Pocket*> pockets)
        :m_table(m_table),m_balls(balls),m_pockets(pockets)
    {}
    PoolGame(Table * m_table, std::vector<Ball*> balls, std::vector<Pocket*> pockets, size_t stage)
        :m_table(m_table),m_balls(balls),m_stage(stage),m_pockets(pockets)
    {}

    void linkQWidgetParentToCueBall(QWidget* parent);

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

    size_t stage(){ return m_stage; }
    void deleteBall(Ball &b);

private:
    /**
     * @brief collide two balls if they are in contact
     * @param b1
     * @param b2
     */
    void collision(Ball &b1, Ball &b2);

    /**
     * @brief collide a ball with a wall if any part of the ball is outside the bounds of the table
     * @param t
     * @param b
     */
    void collision(Table &t, Ball &b);

    void collision(Ball &b1, Pocket &p1);

    Table * m_table;
    size_t m_stage;
    std::vector<Ball*> m_balls;
    std::vector<Pocket*> m_pockets;
};

#endif // POOLGAME_H
