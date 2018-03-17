#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

namespace week02 {
    class Vehicle {

    // Can be accessed by anything
    public:

        // Constructor
        Vehicle(int numberOfPassengers,
            int topSpeed,
            int numberOfWheels,
            std::string color = "red")
            : m_numberOfPassengers(numberOfPassengers)
            , m_topSpeed(topSpeed)
            , m_numberOfWheels(numberOfWheels)
            , m_color(color)
        {}

        // Virtual is good practice. Makes sure that inheritance works correctly

        // Destructor - deleted when out of scope
        virtual ~Vehicle() {}

        virtual std::string getColor(){
            return m_color;
        }

        virtual int getTopSpeed(){
            return m_topSpeed;
        }

        virtual int getNumberOfWheels(){
            return m_numberOfWheels;
        }

        virtual int getNumberOfPassengers(){
            return m_numberOfPassengers;
        }

        // If virtual method = 0, this MUST be overwritten
        // This makes vehicle an ABSTRACT CLASS - specicially used as a base class
        virtual int getSafetyRating() = 0;

    // This class and derived classes can access this
    protected:
        int m_numberOfPassengers;
        int m_topSpeed;
        int m_numberOfWheels;
        std::string m_color;
    };
}

#endif // VEHICLE_H
