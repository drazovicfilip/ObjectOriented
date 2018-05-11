#include <math.h>
#include <stdexcept>
#include "vector.h"

Vector::Vector(unsigned int size)
    : m_size(size)
{}

Vector::Vector(const Vector& other)
    : m_size(other.length())
    , m_elements(other.operator[])
{}

float Vector::length() const{
    float length = 0;
    for (int i = 0; i < m_size; i++){
        length += m_elements[i]*m_elements[i];
    }
    length = sqrt(length);
}
