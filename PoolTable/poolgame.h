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
        : m_table(m_table)
        , m_balls(balls)
    {}

    /**
     * @brief PoolGame constructor
     * @param m_table a pointer to a Table object, Poolgame takes ownership of this pointer
     * @param balls a vector of pointers to balls, Poolgame takes ownership of all the contained pointers
     * @param pockets a vector of pointers to pockets, Poolgame takes ownership of all the contained pointers
     */
    PoolGame(Table * m_table, std::vector<Ball*> balls, std::vector<Pocket*> pockets)
        : m_table(m_table)
        , m_balls(balls)
        , m_pockets(pockets)
    {}

    /**
     * @brief PoolGame constructor
     * @param m_table a pointer to a Table object, Poolgame takes ownership of this pointer
     * @param balls a vector of pointers to balls, Poolgame takes ownership of all the contained pointers
     * @param pockets a vector of pointers to pockets, Poolgame takes ownership of all the contained pointers
     * @param stage the stage of the assignment used, specified in the JSON file
     */
    PoolGame(Table * m_table, std::vector<Ball*> balls, std::vector<Pocket*> pockets, size_t stage)
        : m_table(m_table)
        , m_stage(stage)
        , m_balls(balls)
        , m_pockets(pockets)
    {}

    /**
     * @brief linkQWidgetParentToCueBall will make sure that the cue ball (BallDecorator type) has the Dialog assigned as a parent, in order for it to handle mouse events
     * @param parent should be the dialog class (which is a QWidget)
     */
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
    QSize size(){ return QSize(m_table->width(), m_table->height()); }

    /**
     * @brief stage
     * @return the stage used
     */
    size_t stage(){ return m_stage; }

    /**
     * @brief deleteBall will delete the given ball from the array of m_balls. This is called if collisions break the ball, or it is swallowed by a pocket
     * @param b the ball to delete
     */
    void deleteBall(Ball &b);

    /**
     * @brief toggleChildrenVisibility will loop through all balls and toggle their visibility if they are CompositeBalls
     */
    void toggleChildrenVisibility();

private:
    /**
     * @brief collide two balls if they are in contact. This will also check if the balls will shatter due to the impact
     * @param b1
     * @param b2
     */
    void collision(Ball &b1, Ball &b2);

    /**
     * @brief collide a ball with a wall if any part of the ball is outside the bounds of the table. This will also check if the ball will shatter due to the impact
     * @param t
     * @param b
     */
    void collision(Table &t, Ball &b);

    /**
     * @brief collide a ball with a pocket. If the pocket engulfs the whole ball, it will delete it
     * @param b1
     * @param p1
     */
    void collision(Ball &b1, Pocket &p1);

    Table * m_table;
    size_t m_stage;
    std::vector<Ball*> m_balls;
    std::vector<Pocket*> m_pockets;
};

#endif // POOLGAME_H
