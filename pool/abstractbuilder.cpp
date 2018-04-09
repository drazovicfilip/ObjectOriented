#include "abstractbuilder.h"

Ball buildBall(Coordinate coordinate, std::string color, int mass, int radius, double xVelocity, double yVelocity){
    return Ball(coordinate, color, mass, radius, xVelocity, yVelocity);
}

Table buildTable(unsigned int length, unsigned int height, unsigned int thickness, unsigned int space, unsigned int friction){
    return Table(length, height, thickness, space, friction);
}

Pool getPool(){
    return Pool();
}
