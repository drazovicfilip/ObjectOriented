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
    Ball(Coordinate coordinate, std::string color, unsigned int mass, unsigned int radius, int xVelocity, int yVelocity);

    virtual ~Ball();
    void render(QPainter &painter, unsigned int time);

    collisionLocation isCollision();

    unsigned int getRadius(){
        return m_radius;
    }

    unsigned int getMass(){
        return m_mass;
    }

    std::string getColor(){
        return *m_color;
    }

    unsigned int getXVelocity(){
        return m_xVelocity;
    }

    unsigned int getYVelocity(){
        return m_yVelocity;
    }

private:
    Coordinate m_coordinate;
    unsigned int m_radius;
    unsigned int m_mass;
    double m_xVelocity;
    double m_yVelocity;
    std::string* m_color;
};

#endif // BALL_H
