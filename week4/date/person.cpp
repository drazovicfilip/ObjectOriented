#include "person.h"
#include <iostream>
#include "date.h"

using namespace Week4;

Person::Person(std::string firstName,
               std::string surname,
               Date dateOfBirth)
       : m_firstName(firstName)
       , m_surname(surname)
       , m_dateOfBirth(dateOfBirth)
{}

Person::~Person(){}

void Person::changeFirstName(std::string firstName){
    m_firstName = firstName;
}

void Person::changeSurname(std::string surname){
    m_surname = surname;
}

std::string Person::getFirstName(){
    return m_firstName;
}

std::string Person::getSurname(){
    return m_surname;
}

int Person::getYearOfBirth(){
    return m_dateOfBirth.getYear();
}

int Person::getCurrentAge(){
    return (2018 - m_dateOfBirth.getYear());
}
