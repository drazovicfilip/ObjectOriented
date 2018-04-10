#ifndef TABLE_H
#define TABLE_H

#include <QPainter>
#include <QPen>
#include <QBrush>

class Table
{
public:
    Table(float length, float height, float thickness, float space, float friction, std::string color);

    virtual ~Table();

    float getLength(){
        return m_length;
    }
    float getHeight(){
        return m_height;
    }
    float getThickness(){
        return m_thickness;
    }
    float getSpace(){
        return m_space;
    }
    float getFriction(){
        return m_friction;
    }
    std::string getColour(){
        return *m_color;
    }

    void render(QPainter &painter);

private:
    float m_length;
    float m_height;
    float m_thickness;
    float m_space;
    float m_friction;
    std::string* m_color;
};

#endif // TABLE_H
