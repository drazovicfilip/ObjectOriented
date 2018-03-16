#ifndef VEHICLE_H
#define VEHICLE_H

#endif // VEHICLE_H

#include <string>

namespace week02 {
    class Vehicle {

    // Can be accessed by anything
    public:

        // Constructor
        Vehicle(int numberOfPassengers,
            int topSpeed,
            int numberOfWheels,
            std::string color = "red");

        // Virtual is good practice. Makes sure that inheritance works correctly

        // Destructor
        virtual ~Vehicle();

        virtual std::string getColor(){
            return m_color;
        }

        virtual int getTopSpeed();

        virtual int getNumberOfWheels();

        virtual int getNumberOfPassengers();

        virtual int getSafetyRating() = 0;

    // This class and derived classes can access this
    protected:
        int m_numberOfPassengers;
        int m_topSpeed;
        int m_numberOfWheels;
        std::string m_color;
    };
}
