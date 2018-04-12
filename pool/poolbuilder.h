#ifndef POOLBUILDER_H
#define POOLBUILDER_H

#include "abstractbuilder.h"
#include "poolfactory.h"

/**
 * @brief The PoolBuilder is a concrete implementation of the abstract builder.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * It will construct balls, a table and an empty pool game for use by the director.
 * This abstracts the class creation process from the client, and generally is good for neatness.
 */

class PoolBuilder : public AbstractBuilder
{
public:

    using AbstractBuilder::buildBall;
    /**
     * @brief buildBall will construct a new ball using a factory, passing it all the given parameters
     * @param coordinate
     * @param color
     * @param mass
     * @param radius
     * @param xVelocity
     * @param yVelocity
     * @return
     */
    virtual Ball* buildBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity);

    using AbstractBuilder::buildTable;
    /**
     * @brief buildTable will construct a new table using a factory, passing it all the given parameters
     * @param length
     * @param height
     * @param thickness
     * @param space
     * @param friction
     * @param color
     * @return
     */
    virtual Table* buildTable(float length, float height, float thickness, float space, float friction, std::string color);

    virtual Pool getPool();

private:
    PoolFactory m_factory;

};

#endif // POOLBUILDER_H
