#ifndef CAR_H
#define CAR_H

#include "motorvehicle.h"
using namespace week02;

class Car : public MotorVehicle {

    public:
        Car(int numberOfPassengers,
            int topSpeed,
            double kilometresPerLitre,
            int numberOfAirBags = 2,
            bool abs = true,
            int numberOfWheels = 4);

        Car(int numberOfPassengers,
            int topSpeed,
            double kilometresPerLitre,
            std::string color,
            int numberOfAirBags = 3,
            bool abs = true,
            int numberOfWheels = 4);

    virtual int getSafetyRating();

    virtual int getNumberOfAirBags() {
        return m_numberOfAirBags;
    }

    virtual bool getAbs() {
        return m_abs;
    }

    virtual ~Car() {}

    // New variables
    private:
        bool m_abs;
        int m_numberOfAirBags;

    };

#endif // CAR_H
