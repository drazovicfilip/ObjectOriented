#ifndef MOTORVEHICLE_H
#define MOTORVEHICLE_H

#endif // MOTORVEHICLE_H

#include "Vehicle.h"

namespace week02 {
    class MotorVehicle : public Vehicle {
    public:
        MotorVehicle(int numberOfPassengers,
            int topSpeed,
            int numberOfWheels,
            double kilometresPerLitre);

        MotorVehicle(int numberOfPassengers,
            int topSpeed,
            int numberOfWheels,
            std::string color,
            double kilometresPerLitre);

        virtual ~MotorVehicle();

        virtual double getKilometresPerLitre();

    protected:
        double m_kmpl;
    };
}
