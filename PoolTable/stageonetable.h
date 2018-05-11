#ifndef STAGEONETABLE_H
#define STAGEONETABLE_H

#include <QColor>
#include <QPainter>

#include "table.h"

/**
 * @brief The StageOneTable class is a concrete version of the Table class specific to stage one of the assignment
 */
class StageOneTable : public Table
{
public:
    StageOneTable(float width, float height,float friction, const QColor &colour)
        :Table(width,height,friction),m_colour(colour)
    {}

    // Table interface
public:
    /**
     * @brief draw the table, it is just a rectangle of width() and height()
     * with the colour set in the constructor
     * @param p the painter used to draw the table
     */
    void draw(QPainter &p);

private:
    QColor m_colour;
};

#endif // STAGEONETABLE_H
