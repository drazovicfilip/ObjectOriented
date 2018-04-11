#ifndef TABLE_H
#define TABLE_H

#include "abstracttable.h"

class Table : public AbstractTable
{
public:
    Table(float length, float height, float thickness, float space, float friction, std::string color);

};
#endif // TABLE_H
