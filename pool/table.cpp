#include "table.h"

Table::Table(float length, float height, float thickness, float space, float friction, std::string color)
    : m_length(length)
    , m_height(height)
    , m_thickness(thickness)
    , m_space(space)
    , m_friction(friction)
    , m_color(new std::string(color))
{}

Table::~Table(){}

void Table::render(QPainter &painter){

    QPen pen;
    pen.setWidth(m_thickness);
    pen.setColor("#643D1A");

    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(QString::fromStdString(*m_color))));

    painter.drawRect(m_space,m_space,(m_length-2*m_space),(m_height-2*m_space));
}
