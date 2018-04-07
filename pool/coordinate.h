#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

class Coordinate
{
public:
    Coordinate(int xCoordinate,
        int yCoordinate,
        unsigned int frameHeight,
        unsigned int frameWidth)
        : m_xCoordinate(xCoordinate)
        , m_yCoordinate(yCoordinate)
        , m_frameHeight(frameHeight)
        , m_frameWidth(frameWidth)
    {}

    int getQtRenderingXCoordinate(){
        return m_xCoordinate;
    }

    int getQtRenderingYCoordinate(){
        return m_frameHeight - m_yCoordinate;
    }

    int getYCoordinate(){
        return m_yCoordinate;
    }

    void changeInXCoordinate(double change){
        m_xCoordinate += (int)change;
    }

    void changeInYCoordinate(double change){
        m_yCoordinate += (int)change;
    }

    void setYCoordinateToZero(double offset){
        m_yCoordinate = (int)offset;
    }

    unsigned int getFrameHeight(){
        return m_frameHeight;
    }

    unsigned int getFrameWidth(){
        return m_frameWidth;
    }

private:
    int m_xCoordinate;
    int m_yCoordinate;
    unsigned int m_frameHeight;
    unsigned int m_frameWidth;
};

#endif // COORDINATE_H
