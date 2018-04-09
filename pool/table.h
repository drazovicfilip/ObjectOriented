#ifndef TABLE_H
#define TABLE_H

#include <QPainter>
#include <QPen>
#include <QBrush>

class Table
{
public:
    Table();
    Table(unsigned int length, unsigned int height, unsigned int thickness, unsigned int space, unsigned int friction);

    virtual ~Table();

    unsigned int getLength(){
        return m_length;
    }
    unsigned int getHeight(){
        return m_height;
    }
    unsigned int getThickness(){
        return m_thickness;
    }
    unsigned int getSpace(){
        return m_space;
    }
    unsigned int getFriction(){
        return m_friction;
    }

    void render(QPainter &painter, unsigned int time);

private:
    unsigned int m_length;
    unsigned int m_height;
    unsigned int m_thickness;
    unsigned int m_space;
    unsigned int m_friction;
};

#endif // TABLE_H
