#include "table.h"

Table::Table()
    : m_length(1000)
    , m_height(600)
    , m_thickness(20)
    , m_space(50)
    , m_friction(1)
{}

Table::Table(float length, float height, float thickness, float space, float friction)
    : m_length(length)
    , m_height(height)
    , m_thickness(thickness)
    , m_space(space)
    , m_friction(friction)
{}

Table::~Table(){}

void Table::render(QPainter &painter){

    QPen pen;
    pen.setWidth(m_thickness);
    pen.setColor("#643D1A");
    QBrush brush("#33641A");

    painter.setPen(pen);
    painter.setBrush(brush);

    painter.drawRect(m_space,m_space,(m_length-2*m_space),(m_height-2*m_space));
}
