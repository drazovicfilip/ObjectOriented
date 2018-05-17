#ifndef STAGETWOPOCKET_H
#define STAGETWOPOCKET_H

#include "pocket.h"

#include <QColor>
#include <QPainter>

/**
 * @brief The StageTwoPocket class is a concrete implementation of pocket.h, for stage 2 of the assignment. Nothing has really changed, just that draw() is implemented
 */
class StageTwoPocket : public Pocket
{
public:
    StageTwoPocket();

    /**
     * @brief draw the pocket
     * @param p
     */
    void draw(QPainter & p);
};

#endif // STAGETWOPOCKET_H
