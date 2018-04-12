#ifndef ABSTRACTBALL_H
#define ABSTRACTBALL_H

#include "coordinate.h"
#include <QPainter>

/**
 * @brief An abstract ball class.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * Each ball will have a given coordinate, velocity, mass, radius and colour.
 * Balls will render themselves.
 */


class AbstractBall
{
public:

    // Constructor. The only way a ball is made is if all parameters are known
    AbstractBall(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity)
        : m_coordinate(coordinate)
        , m_color(new std::string(color))
        , m_mass(mass)
        , m_radius(radius)
        , m_xVelocity(xVelocity)
        , m_yVelocity(yVelocity)
    {}

    // Destructor. Must delete the dynamically allocated color string
    virtual ~AbstractBall(){
        delete m_color;
    }

    /**
     * @brief render - Each ball will render itself. This draws a at the given (x,y) coordinate in the given colour
     * @param painter
     */
    void render(QPainter &painter){
        painter.setPen (Qt::black);
        painter.setBrush(QBrush(QColor(QString::fromStdString(*m_color))));
        painter.drawEllipse(m_coordinate.getQtRenderingXCoordinate() - m_radius,
            m_coordinate.getQtRenderingYCoordinate() - m_radius,
            m_radius * 2,
            m_radius * 2);
    }

    // Get methods
    Coordinate getCoordinate(){
        return m_coordinate;
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

    // Set methods
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


private:
    Coordinate m_coordinate;
    std::string* m_color;
    float m_mass;
    float m_radius;
    float m_xVelocity;
    float m_yVelocity;
};

#endif // ABSTRACTBALL_H
