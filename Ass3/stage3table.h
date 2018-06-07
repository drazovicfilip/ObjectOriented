#ifndef STAGE3TABLE_H
#define STAGE3TABLE_H
#include <QColor>
#include <QPainter>
#include <vector>

#include "table.h"
#include "pocket.h"
/**
 * @brief The Stage3Table class is a concrete version of the Table class specific to stage one of the assignment
 */
class Stage3Table : public Table
{
public:
    Stage3Table(float width, float height,float friction, const QColor &colour, std::vector<Pocket*> pockets)
        :Table(width,height,friction),m_colour(colour),m_pockets(pockets)
        , shakeframes(0)
        , prevShake(QVector2D(0,0))
    {}

    // Table interface
public:
    /**
     * @brief draw the table, it is just a rectangle of width() and height()
     * with the colour set in the constructor
     * @param p the painter used to draw the table
     */
    void draw(QPainter &p);
    void shake(){ shakeframes += 30; }

private:
    QColor m_colour;
    int shakeframes;
    QVector2D prevShake;
    std::vector<Pocket*> m_pockets;

    // Table interface
public:
    ChangeInPoolGame ballCollision(Ball *b);
};
#endif // STAGE3TABLE_H
