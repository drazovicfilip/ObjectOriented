#include "pool.h"

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
