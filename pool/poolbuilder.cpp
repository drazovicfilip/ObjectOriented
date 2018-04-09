#include "poolbuilder.h"
#include "poolfactory.h"

Ball* PoolBuilder::buildBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity) {
    PoolFactory factory;
    return factory.createBall(coordinate, color, mass, radius, xVelocity, yVelocity);
}

Table* PoolBuilder::buildTable(float length, float height, float thickness, float space, float friction) {
    PoolFactory factory;
    return factory.createTable(length, height, thickness, space, friction);
}

Pool PoolBuilder::getPool(){
    return Pool();
}
