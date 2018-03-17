#include "car.h"

using namespace week02;

// Without given colour
Car::Car(int numberOfPassengers,
         int topSpeed,
         double kilometresPerLitre,
         int numberofAirBags,
         bool abs,
         int numberOfWheels)

    // Variables that were inherited
    : MotorVehicle(numberOfPassengers, topSpeed, numberOfWheels, kilometresPerLitre)

    // New variables
    , m_abs(abs)
    , m_numberOfAirBags(numberofAirBags)
{}

// If given colour
Car::Car(int numberOfPassengers,
         int topSpeed,
         double kilometresPerLitre,
         std:: string color,
         int numberofAirBags,
         bool abs,
         int numberOfWheels)

    // Variables that were inherited
    : MotorVehicle(numberOfPassengers, topSpeed, numberOfWheels, color, kilometresPerLitre)

    // New variables
    , m_abs(abs)
    , m_numberOfAirBags(numberofAirBags)
{}

int Car::getSafetyRating() {
    int safetyRating = 0;
    if (m_numberOfAirBags >= 4) {
        safetyRating += 3;
    } else if (m_numberOfAirBags >= 2) {
        safetyRating += 2;
    } else if (m_numberOfAirBags > 0) {
        safetyRating += 1;
    }

    if (m_abs) {
        safetyRating += 2;
    }
    return safetyRating;
}
