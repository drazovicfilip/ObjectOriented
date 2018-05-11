#ifndef STAGETWOPOCKET_H
#define STAGETWOPOCKET_H

#include "pocket.h"

#include <QColor>
#include <QPainter>

class StageTwoPocket : public Pocket
{
public:
    StageTwoPocket();
    void draw(QPainter & p);
};

#endif // STAGETWOPOCKET_H
