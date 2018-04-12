#include "table.h"

/**
 * @brief The Table is a concrete implementation of the abstract table, with nothing changed.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * It is a static, drawn object that doesn't move during runtime.
 * It holds the boundaries of the pool game which are used for colision calculations.
 * These parameters should not change during runtime.
 */

Table::Table(float length, float height, float thickness, float space, float friction, std::string color)
    : AbstractTable(length, height, thickness, space, friction, color)
{}

