#include "person.h"
#include "student.h"

namespace Week4
{
Student::Student(const std::string &givenName, const std::string &surname,
                 const Date &date, const std::string &degree)
        : Person(givenName, surname, date)
        , m_degree(new std::string(degree))
{}

Student::~Student(){
    delete m_degree;
}

std::string Student::getRecord() const{
    std::stringstream ss;
    ss << "Name: " << getFirstName() << " " << getSurname() << std::endl;
    ss << "Date of Birth: " << m_dateOfBirth.dateAsString() << std::endl;
    ss << "Degree: " << *m_degree << std::endl;
    m_recordAccessed++;
    return ss.str();
}

}
