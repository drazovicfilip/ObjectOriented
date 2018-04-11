#ifndef ABSTRACTBALL_H
#define ABSTRACTBALL_H

#include "coordinate.h"
#include <QPainter>


class AbstractBall
{
public:

    AbstractBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity)
        : m_coordinate(coordinate)
        , m_radius(radius)
        , m_mass(mass)
        , m_xVelocity(xVelocity)
        , m_yVelocity(yVelocity)
        , m_color(new std::string(color))
    {}

    virtual ~AbstractBall(){
        delete m_color;
    }

    void render(QPainter &painter){
        painter.setPen (Qt::black);
        painter.setBrush(QBrush(QColor(QString::fromStdString(*m_color))));
        painter.drawEllipse(m_coordinate.getQtRenderingXCoordinate() - m_radius,
            m_coordinate.getQtRenderingYCoordinate() - m_radius,
            m_radius * 2,
            m_radius * 2);
    }

    Coordinate getCoordinate(){
        return m_coordinate;
    }

    void changeinXCoordinate(float value){
        m_coordinate.changeInXCoordinate(value);
    }
    void changeinYCoordinate(float value){
        m_coordinate.changeInYCoordinate(value);
    }

    void flipXVelocity(){
        m_xVelocity = m_xVelocity * -1.0;
    }

    void flipYVelocity(){
        m_yVelocity = m_yVelocity * -1.0;
    }

    void changeXVelocity(float change){
        m_xVelocity += change;
    }

    void changeYVelocity(float change){
        m_yVelocity += change;
    }

    float getRadius(){
        return m_radius;
    }

    float getMass(){
        return m_mass;
    }

    std::string getColor(){
        return *m_color;
    }

    float getXVelocity(){
        return m_xVelocity;
    }

    float getYVelocity(){
        return m_yVelocity;
    }


private:
    Coordinate m_coordinate;
    float m_radius;
    float m_mass;
    float m_xVelocity;
    float m_yVelocity;
    std::string* m_color;
};

#endif // ABSTRACTBALL_H
