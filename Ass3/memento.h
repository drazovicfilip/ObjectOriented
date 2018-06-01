#ifndef MEMENTO_H
#define MEMENTO_H

#include "ball.h"

class Memento
{
    Memento(std::vector<Ball*>  state);

    std::vector<Ball*>  getSavedState(){ return m_state; }

    std::vector<Ball*>  m_state;

    friend class Originator;
};

#endif // MEMENTO_H
