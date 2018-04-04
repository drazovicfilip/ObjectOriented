#ifndef BALL_H
#define BALL_H

#include "coordinate.h"
#include <QPainter>

#define fwidth 1000
#define fheight 600
#define outsidedist 50
#define tablethickness 20

enum BallType{ stripe, solid, cue, black };
enum collisionLocation{vertical, horizontal, none};

class Ball
{

public:
    Ball(Coordinate coordinate);
    Ball(Coordinate coordinate, int xVelocity, int yVelocity);
    Ball(Coordinate coordinate, std::string color, BallType type);
    virtual ~Ball();
    void render(QPainter &painter, unsigned int time);

    collisionLocation isCollision();

    unsigned int getRadius(){
        return m_radius;
    }

private:
    Coordinate m_coordinate;
    unsigned int m_radius;
    double m_xVelocity;
    double m_yVelocity;
    std::string* m_color;
    BallType m_type;
};

#endif // BALL_H
