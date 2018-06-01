#ifndef ORIGINATOR_H
#define ORIGINATOR_H

#include "memento.h"
#include <iostream>

class Originator
{
public:
    virtual ~Originator(){}

    void set(std::vector<Ball*>  state){
        m_state = state;
    }

    Memento* saveToMemento(){ return new Memento(m_state); }

    void restoreFromMemento(Memento memento){ m_state = memento.getSavedState(); }

    std::vector<Ball*> state(){ return m_state; }

private:
    std::vector<Ball*>  m_state;
};

#endif // ORIGINATOR_H
