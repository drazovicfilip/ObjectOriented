#include "poolbuilder.h"
#include "poolfactory.h"

Ball* PoolBuilder::buildBall(Coordinate coordinate, std::string color, int mass, int radius, double xVelocity, double yVelocity) {
    PoolFactory factory;
    return factory.createBall(coordinate, color, mass, radius, xVelocity, yVelocity);
}

Table* PoolBuilder::buildTable(unsigned int length, unsigned int height, unsigned int thickness, unsigned int space, unsigned int friction) {
    PoolFactory factory;
    return factory.createTable(length, height, thickness, space, friction);
}

Pool PoolBuilder::getPool(){
    return Pool();
}
