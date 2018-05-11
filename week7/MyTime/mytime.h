#ifndef TIME_H
#define TIME_H

#include <string>
#include <sstream>

namespace Week07 {
class Time
{
public:
    Time()
        : m_hours(0)
        , m_minutes(0)
        , m_seconds(0)
    {}

    Time(int hours, int minutes, int seconds)
        : m_hours(hours)
        , m_minutes(minutes)
        , m_seconds(seconds)
    {}

    Time(const Time &time){
        m_hours = time.numberOfHours();
        m_minutes = time.numberOfMinutes() - time.numberOfHours()*60;
        m_seconds = time.numberOfSeconds() - time.numberOfMinutes()*60;
    }

    Time& operator=(const Time &time){
        this->m_hours = time.numberOfHours();
        this->m_minutes = time.numberOfMinutes() - time.numberOfHours()*60;
        this->m_seconds = time.numberOfSeconds() - time.numberOfMinutes()*60;
        return *this;
    }

    Time operator+(const Time &time){
        Time newtime(( this->numberOfHours() + time.numberOfHours() ),
                     ( this->numberOfMinutes()-this->numberOfHours()*60 + (time.numberOfMinutes()-time.numberOfHours()*60) ),
                     ( this->numberOfSeconds()-this->numberOfMinutes()*60) + (time.numberOfSeconds()-time.numberOfMinutes()*60) );
        return newtime;
    }
    Time operator-(const Time &time){
        Time newtime(( this->numberOfHours() - time.numberOfHours() ),
                     ( this->numberOfMinutes()-this->numberOfHours()*60 - (time.numberOfMinutes()-time.numberOfHours()*60) ),
                     ( this->numberOfSeconds()-this->numberOfMinutes()*60) - (time.numberOfSeconds()-time.numberOfMinutes()*60)  );
        return newtime;
    }

    double numberOfHours() const{
        return m_hours;
    }
    double numberOfMinutes() const{
        return m_hours*60 + m_minutes;
    }
    int numberOfSeconds() const{
        return (m_hours*60 + m_minutes)*60 + m_seconds;
    }

    std::string getTimeAsString() const{
        std::stringstream ss;

        // Put in hours
        if (m_hours > 9){ ss << m_hours << ":"; }
        else{ ss << "0" << m_hours << ":"; }

        // Put in minutes
        if (m_minutes > 9){ ss << m_minutes << ":"; }
        else{ ss << "0" << m_minutes << ":"; }

        // Put in seconds
        if (m_seconds > 9){ ss << m_seconds; }
        else{ ss << "0" << m_seconds; }

        return ss.str();
    }

private:
    int m_hours;
    int m_minutes;
    int m_seconds;
};
}
#endif
