#ifndef BICYCLE_H
#define BICYCLE_H

#include "vehicle.h"
using namespace week02;

class Bicycle: public Vehicle{

    public:
        Bicycle(int numberOfPassengers,
            int topSpeed,
            bool helmetUsed = false,
            int numberOfWheels = 2);

        Bicycle(int numberOfPassengers,
            int topSpeed,
            std::string color,
            bool helmetUsed = false,
            int numberOfWheels = 2);

    virtual int getSafetyRating();

    virtual bool getHelmedUsed(){
        return m_helmetUsed;
    }

    private:
        bool m_helmetUsed;

};

#endif // BICYCLE_H
