#include "pool.h"

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

/**
 * @brief render - The pool object will render itself. This will call each of its children (balls, table) to render themselves
 * @param painter
 */
void Pool::render(QPainter &painter){
    m_table->render(painter);
    for (Ball * currentball : m_balls){
        currentball->render(painter);
    }
}

/**
 * @brief setTable will allocate a given table object to be the table for this pool game
 * @param table
 */
void Pool::setTable(Table* table){
    m_table = table;
}

/**
 * @brief addBall will append a given ball object to the vector of balls for this pool game
 * @param ball
 */
void Pool::addBall(Ball* ball){
    m_balls.push_back(ball);
}

// Get methods
Table* Pool::getTable(){
    return m_table;
}

std::vector<Ball *> Pool::getBalls(){
    return m_balls;
}
