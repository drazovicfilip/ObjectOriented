#ifndef MOTORVEHICLE_H
#define MOTORVEHICLE_H

#endif // MOTORVEHICLE_H

#include "vehicle.h"

namespace week02 {

    // MotorVehicle inherits from Vehicle
    class MotorVehicle : public Vehicle {
    public:

        // Without given colour
        MotorVehicle(int numberOfPassengers,
                    int topSpeed,
                    int numberOfWheels,
                    double kilometresPerLitre)
                    : Vehicle(numberOfPassengers, topSpeed, numberOfWheels)
                    , m_kmpl(kilometresPerLitre)
        {}

        // With given colour
        MotorVehicle(int numberOfPassengers,
            int topSpeed,
            int numberOfWheels,
            std::string color,
            double kilometresPerLitre)
            : Vehicle(numberOfPassengers, topSpeed, numberOfWheels, color)
            , m_kmpl(kilometresPerLitre)
        {}

        virtual ~MotorVehicle(){}

        virtual double getKilometresPerLitre(){
            return m_kmpl;
        }

    protected:
        double m_kmpl;
    };
}
