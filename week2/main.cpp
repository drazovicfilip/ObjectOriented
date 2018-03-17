#include <iostream>
#include "car.h"
#include "bus.h"

using namespace week02;

    int main(int argc, char* argv[]) {

        std::cout << "Hello World!" << std::endl;

        Bus bus1(1,75,10);
        std::cout << bus1.getSafetyRating() << std::endl;
        std::cout << bus1.getColor() << std::endl;
        std::cout << bus1.getKilometresPerLitre()<< std::endl;

        return 0;
    }
