#ifndef POCKET_H
#define POCKET_H

#include <QVector2D>
#include <QPainter>

class Pocket
{
public:
    Pocket(){}
    virtual ~Pocket(){}

    // Get methods
    float radius() const{ return m_radius; }
    const QVector2D &position() const{ return m_position; }

    // Set methods
    void setPosition(const QVector2D &newPosition){ m_position = newPosition; }
    void setRadius(float newRadius){ m_radius = newRadius; }

    virtual void draw(QPainter &p) = 0;
protected:
    QVector2D m_position;
    float m_radius;
};

#endif // POCKET_H
