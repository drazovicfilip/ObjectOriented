#include "bicycle.h"

using namespace week02;

Bicycle::Bicycle(int numberOfPassengers,
                 int topSpeed,
                 bool helmetUsed,
                 int numberOfWheels)

            // Variables that were inherited
            : Vehicle(numberOfPassengers, topSpeed, numberOfWheels)

            // New variables
            , m_helmetUsed(helmetUsed)
{}

// With given colour
Bicycle::Bicycle(int numberOfPassengers,
                 int topSpeed,
                 std:: string color,
                 bool helmetUsed,
                 int numberOfWheels)

            // Variables that were inherited
            : Vehicle(numberOfPassengers, topSpeed, numberOfWheels, color)

            // New variables
            , m_helmetUsed(helmetUsed)
{}

int Bicycle::getSafetyRating() {
    if (m_helmetUsed) {
        return 5;
    } else {
        return 0;
    }
}

