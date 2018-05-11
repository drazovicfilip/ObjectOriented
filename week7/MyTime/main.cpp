#include <QCoreApplication>
#include "mytime.h"
#include <iostream>

    int main(int argc, char *argv[])
    {
        Week07::Time time1(8, 4, 3);
        Week07::Time time2(time1);
        Week07::Time time3 = time1 + time2;
        Week07::Time time4 = time3 - time2;
        Week07::Time time5 = time4;
        std::cout << time1.getTimeAsString() << std::endl;
        std::cout << time2.getTimeAsString() << std::endl;
        std::cout << time3.getTimeAsString() << std::endl;
        std::cout << time4.getTimeAsString() << std::endl;
        std::cout << time5.getTimeAsString() << std::endl;
        return 0;
    }

