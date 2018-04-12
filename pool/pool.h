#ifndef POOL_H
#define POOL_H

#include "table.h"
#include "ball.h"
#include <vector>
#include <QPainter>

/**
 * @brief The Pool class holds all the balls and the table.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * It will render itself, and has methods that allow for a table to be specified and
 * balls to be added. These will be called upon by the constructor, which will build
 * all balls and the table as necessary.
 */

class Pool{
public:

    /**
     * @brief render - The pool object will render itself. This will call each of its children (balls, table) to render themselves
     * @param painter
     */
    void render(QPainter &painter);

    /**
     * @brief setTable will allocate a given table object to be the table for this pool game
     * @param table
     */
    void setTable(Table* table);

    /**
     * @brief addBall will append a given ball object to the vector of balls for this pool game
     * @param ball
     */
    void addBall(Ball* ball);

    // Get methods
    Table* getTable();
    std::vector<Ball *> getBalls();

private:
    Table* m_table;
    std::vector<Ball *> m_balls;
};

#endif // POOL_H
