#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>
#include <math.h>

class Coordinate
{
public:
    Coordinate(float xCoordinate,
        float yCoordinate,
        float frameHeight,
        float frameWidth)
        : m_xCoordinate(xCoordinate)
        , m_yCoordinate(yCoordinate)
        , m_frameHeight(frameHeight)
        , m_frameWidth(frameWidth)
    {}

    float getQtRenderingXCoordinate(){
        return m_xCoordinate;
    }

    float getQtRenderingYCoordinate(){
        return m_frameHeight - m_yCoordinate;
    }

    float getYCoordinate(){
        return m_yCoordinate;
    }

    void changeInXCoordinate(float change){
        m_xCoordinate += change;
    }

    void changeInYCoordinate(float change){
        m_yCoordinate += change;
    }

    void setYCoordinateToZero(float offset){
        m_yCoordinate = ceil(offset);
    }

    float getFrameHeight(){
        return m_frameHeight;
    }

    float getFrameWidth(){
        return m_frameWidth;
    }

private:
    float m_xCoordinate;
    float m_yCoordinate;
    float m_frameHeight;
    float m_frameWidth;
};

#endif // COORDINATE_H
