#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

class Coordinate
{
public:
    Coordinate(unsigned int xCoordinate,
        unsigned int yCoordinate,
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

    void changeInXCoordinate(int change){
        m_xCoordinate += change;
    }

    void changeInYCoordinate(int change){
        m_yCoordinate += change;
    }

    void setYCoordinateToZero(int offset){
        m_yCoordinate = offset;
    }

    unsigned int getFrameHeight(){
        return m_frameHeight;
    }

    unsigned int getFrameWidth(){
        return m_frameWidth;
    }

private:
    unsigned int m_xCoordinate;
    unsigned int m_yCoordinate;
    unsigned int m_frameHeight;
    unsigned int m_frameWidth;
};

#endif // COORDINATE_H
