#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

class Coordinate
{
public:
    Coordinate(double xCoordinate,
        double yCoordinate,
        unsigned int frameHeight,
        unsigned int frameWidth)
        : m_xCoordinate(xCoordinate)
        , m_yCoordinate(yCoordinate)
        , m_frameHeight(frameHeight)
        , m_frameWidth(frameWidth)
    {}

    double getQtRenderingXCoordinate(){
        return m_xCoordinate;
    }

    double getQtRenderingYCoordinate(){
        return m_frameHeight - m_yCoordinate;
    }

    double getYCoordinate(){
        return m_yCoordinate;
    }

    void changeInXCoordinate(double change){
        m_xCoordinate += change;
    }

    void changeInYCoordinate(double change){
        m_yCoordinate += change;
    }

    void setYCoordinateToZero(double offset){
        m_yCoordinate = offset;
    }

    unsigned int getFrameHeight(){
        return m_frameHeight;
    }

    unsigned int getFrameWidth(){
        return m_frameWidth;
    }

private:
    double m_xCoordinate;
    double m_yCoordinate;
    unsigned int m_frameHeight;
    unsigned int m_frameWidth;
};

#endif // COORDINATE_H
