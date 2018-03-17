#ifndef BUS_H
#define BUS_H


#include "motorvehicle.h"

using namespace week02;

class Bus : public MotorVehicle {
public:
    Bus(int numberOfPassengers,
       int topSpeed,
       double kilometresPerLitre,
       bool seatBeltsInstalled = false,
       bool standingPassengersAllowed = true,
       int numberOfWheels = 6);

    Bus(int numberOfPassengers,
       int topSpeed,
       double kilometresPerLitre,
       std::string color,
       bool seatBeltsInstalled = false,
       bool standingPassengersAllowed = true,
       int numberOfWheels = 6);

    virtual int getSafetyRating();

    virtual int getNumberOfSeatBelts() {
        return m_seatBeltsInstalled;
    }

    virtual int getNumberOfStandingPassengersAllowed() {
        return m_standingPassengersAllowed;
    }

    virtual ~Bus() {}

    // New variables
    private:
        bool m_seatBeltsInstalled;
        int m_standingPassengersAllowed;

};

#endif // BUS_H
