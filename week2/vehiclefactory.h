#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H

#include "vehicle.h"
#include "motorvehicle.h"
#include "bicycle.h"
#include "bus.h"
#include "car.h"

class VehicleFactory
{
   public:
    enum VehicleType {
            FastCar,
            SlowCar,
            BusType,
            BicycleType
        };

    static week02::Vehicle* getVehicle(VehicleType vehicleType);

private:
    VehicleFactory();
};

#endif // VEHICLEFACTORY_H
