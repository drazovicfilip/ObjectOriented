#include <iostream>
#include "car.h"

using namespace week02;

    int main(int argc, char* argv[]) {

        std::cout << "Hello World!" << std::endl;

        // Make a new 'vehicle'

        Car car1(1,75,10,4);
        std::cout << car1.getSafetyRating() << std::endl;

        return 0;
    }
