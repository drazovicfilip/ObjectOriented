#ifndef TABLE_H
#define TABLE_H

#include <QPainter>
#include <QPen>
#include <QBrush>

class Table
{
public:
    Table();
    Table(unsigned int length, unsigned int height, unsigned int thickness, unsigned int space);

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

    void render(QPainter &painter, unsigned int time);

private:
    unsigned int m_length;
    unsigned int m_height;
    unsigned int m_thickness;
    unsigned int m_space;
};

#endif // TABLE_H
