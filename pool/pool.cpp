#include "pool.h"

void Pool::render(QPainter &painter){
    m_table->render(painter);
    for (Ball * currentball : m_balls){
        currentball->render(painter);
    }
}

void Pool::setTable(Table* table){
    m_table = table;
}

void Pool::addBall(Ball* ball){
    m_balls.push_back(ball);
}

Table* Pool::getTable(){
    return m_table;
}

std::vector<Ball *> Pool::getBalls(){
    return m_balls;
}
