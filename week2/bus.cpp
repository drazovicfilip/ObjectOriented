#include "bus.h"

using namespace week02;

// Without given colour
Bus::Bus(int numberOfPassengers,
         int topSpeed,
         double kilometresPerLitre,
         bool seatBeltsInstalled,
         bool standingPassengersAllowed,
         int numberOfWheels)

    // Variables that were inherited
    : MotorVehicle(numberOfPassengers, topSpeed, numberOfWheels, kilometresPerLitre)

    // New variables
    , m_seatBeltsInstalled(seatBeltsInstalled)
    , m_standingPassengersAllowed(standingPassengersAllowed)
{}

// With given colour
Bus::Bus(int numberOfPassengers,
         int topSpeed,
         double kilometresPerLitre,
         std:: string color,
         bool seatBeltsInstalled,
         bool standingPassengersAllowed,
         int numberOfWheels)

    // Variables that were inherited
    : MotorVehicle(numberOfPassengers, topSpeed, numberOfWheels, color, kilometresPerLitre)

    // New variables
    , m_seatBeltsInstalled(seatBeltsInstalled)
    , m_standingPassengersAllowed(standingPassengersAllowed)
{}

int Bus::getSafetyRating() {
    int safetyRating = 0;

    if (m_seatBeltsInstalled) {
        safetyRating += 3;
    }
    if (!m_standingPassengersAllowed) {
        safetyRating += 2;
    }
    return safetyRating;
}

