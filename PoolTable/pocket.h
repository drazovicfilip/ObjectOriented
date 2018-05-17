#ifndef POCKET_H
#define POCKET_H

#include <QVector2D>
#include <QPainter>

/**
 * @brief pocket.h is an abstract class that defines a pocket for use in stage 2+ of the assignment
 */
class Pocket
{
public:
    Pocket(){}
    virtual ~Pocket(){}

    /**
     * @brief radius returns the radius of the pocket
     * @return m_radius - float
     */
    float radius() const{ return m_radius; }

    /**
     * @brief position returns the position of the pocket
     * @return position - QVector2D
     */
    const QVector2D &position() const{ return m_position; }

    /**
     * @brief setPosition will set the position manually to a value
     * @param newPosition - float
     */
    void setPosition(const QVector2D &newPosition){ m_position = newPosition; }

    /**
     * @brief setRadius will set the radius manually to a value
     * @param newRadius - float
     */
    void setRadius(float newRadius){ m_radius = newRadius; }

    virtual void draw(QPainter &p) = 0;

protected:
    QVector2D m_position;
    float m_radius;
};

#endif // POCKET_H
