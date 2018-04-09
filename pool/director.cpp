#include "director.h"

Director::Director(AbstractBuilder* builder)
    : m_builder(builder)
{}

Pool Director::construct(){
    Pool pool = m_builder->getPool();
    pool.setTable(m_builder->buildTable(1000, 600, 20, 50, 1));


    pool.addBall(m_builder->buildBall(Coordinate(fwidth/5, fheight/2, fheight, fwidth), "green", 1, 20, -3, -3));
    pool.addBall(m_builder->buildBall(Coordinate(fwidth/5, fheight/3, fheight, fwidth), "green", 1, 20, 3, 1));
    pool.addBall(m_builder->buildBall(Coordinate(fwidth/5, fheight/4, fheight, fwidth), "green", 1, 20, -5, -3));

    pool.addBall(m_builder->buildBall(Coordinate(fwidth/4, fheight/2, fheight, fwidth), "red", 1, 20, 3, 1));
    pool.addBall(m_builder->buildBall(Coordinate(fwidth/4, fheight/4, fheight, fwidth), "red", 1, 20, 3, 2));


    //pool.addBall(m_builder->buildBall(Coordinate(fwidth/4, fheight/4, fheight, fwidth), "red", 1, 20, -3.25, 1.23));
    return pool;
}
