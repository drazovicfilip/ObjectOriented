#ifndef BALL_H
#define BALL_H

#include "coordinate.h"
#include <QPainter>

#define fwidth 1000
#define fheight 600
#define outsidedist 50
#define tablethickness 20

class Ball
{

public:
    Ball(Coordinate coordinate);
    Ball(Coordinate coordinate, std::string color, float mass, float radius, float xVelocity, float yVelocity);

    virtual ~Ball();
    void render(QPainter &painter);

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

#endif // BALL_H
