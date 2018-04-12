#ifndef ABSTRACTTABLE_H
#define ABSTRACTTABLE_H

#include <QPainter>
#include <QPen>
#include <QBrush>

/**
 * @brief The Table is a static, drawn object that doesn't move during runtime.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * It holds the boundaries of the pool game which are used for colision calculations.
 * These parameters should not change during runtime.
 */

class AbstractTable
{
public:

    // Constructor. The only way a table is made is if all parameters are known
    AbstractTable(float length, float height, float thickness, float space, float friction, std::string color)
        : m_length(length)
        , m_height(height)
        , m_thickness(thickness)
        , m_space(space)
        , m_friction(friction)
        , m_color(new std::string(color))
    {}

    // Destructor. Must delete the dynamically allocated color string
    virtual ~AbstractTable(){
        delete m_color;
    }

    // The table will render itself. This draws a rectangle using the given length, height, thickness and space
    void render(QPainter &painter){

        QPen pen;
        pen.setWidth(m_thickness);
        pen.setColor("#643D1A");

        painter.setPen(pen);
        painter.setBrush(QBrush(QColor(QString::fromStdString(*m_color))));

        painter.drawRect(m_space,m_space,(m_length-2*m_space),(m_height-2*m_space));
    }

    // Get methods
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

private:
    float m_length;
    float m_height;
    float m_thickness;
    float m_space;
    float m_friction;
    std::string* m_color;
};

#endif // ABSTRACTTABLE_H
