#ifndef DUPLICATIONBALLDECORATOR_H
#define DUPLICATIONBALLDECORATOR_H
#include "balldecorator.h"

/**
 * @brief The DuplicationBallDecorator class is a little bonus decorator that duplicates when it hits things
 */
class DuplicationBallDecorator: public BallDecorator
{
public:
    DuplicationBallDecorator(Ball *b)
        : BallDecorator(b)
    {}
    DuplicationBallDecorator* clone(){ return new DuplicationBallDecorator(m_ball); }
    /**
     * @brief changeVelocity this acts like the regular function but can also duplicate the ball whilst decreasing its size
     * @param deltaV
     * @return
     */
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);
};

#endif // DUPLICATIONBALLDECORATOR_H
