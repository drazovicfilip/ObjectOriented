#ifndef BALL_H
#define BALL_H

#include "coordinate.h"
#include <QPainter>

#define fwidth 1000
#define fheight 600
#define outsidedist 50
#define tablethickness 20

enum collisionLocation{vertical, horizontal, none};

class Ball
{

public:
    Ball(Coordinate coordinate);
    Ball(Coordinate coordinate, std::string color, int mass, int radius, double xVelocity, double yVelocity);

    virtual ~Ball();
    void render(QPainter &painter, unsigned int time);

    Coordinate getCoordinate(){
        return m_coordinate;
    }

    void flipXVelocity(){
        m_xVelocity *= -1;
    }

    void flipYVelocity(){
        m_yVelocity *= -1;
    }

    void changeXVelocity(double change){
        m_xVelocity += change;
    }

    void changeYVelocity(double change){
        m_yVelocity += change;
    }

    int getRadius(){
        return m_radius;
    }

    int getMass(){
        return m_mass;
    }

    std::string getColor(){
        return *m_color;
    }

    double getXVelocity(){
        return m_xVelocity;
    }

    double getYVelocity(){
        return m_yVelocity;
    }

private:
    Coordinate m_coordinate;
    int m_radius;
    int m_mass;
    double m_xVelocity;
    double m_yVelocity;
    std::string* m_color;
};

#endif // BALL_H
