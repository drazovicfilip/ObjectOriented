#include "date.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

using namespace Week4;

Date::Date(int day, int month, int year)
    : m_day(day)
    , m_month(month)
    , m_year(year)
{}

Date:: ~Date(){}

int Date::getDay() const{
    return m_day;
}

int Date::getMonth() const{
    return m_month;
}

int Date::getYear() const{
    return m_year;
}

std::string Date::dateAsString() const{
    std::stringstream ss;
    //ss << m_day << '/' << m_month << '/' << m_year;
    ss << getDay() << '/' << getMonth() << '/' << getYear();
    return ss.str();
}
