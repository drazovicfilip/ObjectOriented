#ifndef POOL_H
#define POOL_H

#include "table.h"
#include "ball.h"
#include <vector>

class Pool{
public:
    void setTable(Table* table);
    void addBall(Ball* ball);
    Table* getTable();
    std::vector<Ball *> getBalls();

private:
    Table* m_table;
    std::vector<Ball *> m_balls;
};

#endif // POOL_H
