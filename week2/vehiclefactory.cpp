#include "vehiclefactory.h"

week02::Vehicle* VehicleFactory::getVehicle(VehicleType vehicleType){
    switch(vehicleType)
        {
            case FastCar: return new Car(2,250,8);
            case SlowCar: return new Car(5,100,25);
            case BusType: return new Bus(50,110,2);
            case BicycleType: return new Bicycle(1,70);
        }
        throw "invalid vehicle type";
}

