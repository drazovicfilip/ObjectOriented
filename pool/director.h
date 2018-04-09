#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "poolbuilder.h"

class Director
{
public:
    Director(AbstractBuilder* builder);
    Pool construct();

private:
    AbstractBuilder* m_builder;
};

#endif // DIRECTOR_H
