#ifndef LEAFBALL_H
#define LEAFBALL_H

#include <QColor>
#include <QPainter>
#include <QMouseEvent>

#include "ball.h"
#include <vector>


/**
 * @brief The LeafBall class is part of the Composite design method. It does not have any children, and can be contained in a CompositeBall.
 */
class LeafBall : public Ball
{
public:
    LeafBall();

public:
    void draw(QPainter &p);
};

#endif // LEAFBALL_H
