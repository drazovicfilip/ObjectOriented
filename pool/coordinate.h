#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>
#include <math.h>

/**
 * @brief The Coordinate class is used for any balls in the program
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * Balls are given a coordinate when they are initialised, and this coordinate is
 * updated as the program runs. Every ball also stores the table dimensions, which
 * can be useful for calculating collisions.
 */

class Coordinate
{
public:

    // Constructor. The only way a coordinate is made is if all parameters are known
    Coordinate(float xCoordinate,
        float yCoordinate,
        float frameHeight,
        float frameWidth)
        : m_xCoordinate(xCoordinate)
        , m_yCoordinate(yCoordinate)
        , m_frameHeight(frameHeight)
        , m_frameWidth(frameWidth)
    {}

    // Get methods
    float getQtRenderingXCoordinate(){
        return m_xCoordinate;
    }

    float getQtRenderingYCoordinate(){
        return m_frameHeight - m_yCoordinate;
    }

    float getYCoordinate(){
        return m_yCoordinate;
    }

    float getFrameHeight(){
        return m_frameHeight;
    }

    float getFrameWidth(){
        return m_frameWidth;
    }

    // Set methods

    void changeInXCoordinate(float change){
        m_xCoordinate += change;
    }

    void changeInYCoordinate(float change){
        m_yCoordinate += change;
    }

    void setYCoordinateToZero(float offset){
        m_yCoordinate = ceil(offset);
    }



private:
    float m_xCoordinate;
    float m_yCoordinate;
    float m_frameHeight;
    float m_frameWidth;
};

#endif // COORDINATE_H
