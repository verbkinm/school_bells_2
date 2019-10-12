#include <sstream>
#include <ctime>
#include <iomanip>
#include "time.h"

Time Time::fromLocal_time()
{
    time_t rawtime;
    tm * timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    return {timeinfo->tm_hour, timeinfo->tm_min};
}

Time::Time() : _hours(0), _minutes(0)
{

}

Time::Time(int h, int m)
{
    _hours = h % 24;
    if(_hours < 0)
        _hours += 24;
    _hours += m / 60;

    _minutes = m % 60;
    if(_minutes < 0)
        _minutes += 60;
}

int Time::hours() const
{
    return _hours;
}

int Time::minutes() const
{
    return _minutes;
}

void Time::setHours(int h)
{
    _hours = h % 24;
    if(_hours < 0)
        _hours += 24;
}

void Time::setMinutes(int m)
{
    _minutes = m % 60;
    if(_minutes < 0)
        _minutes += 60;
}

void Time::setFrom_string(std::string str)
{
    int h, m;
    char d;
    std::stringstream ss(str);

    ss >> h;
    ss >> d;
    ss >> m;

    Time t(h,m);

    this->setHours(t.hours());
    this->setMinutes(t.minutes());
}

std::string Time::toString() const
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw (2) << hours()
       << ":"
       << std::setfill('0') << std::setw (2) << minutes();
    return ss.str();
}

bool operator>=(const Time &lhs, const Time &rhs)
{
    return lhs.total_minutes() >= rhs.total_minutes();
}

bool operator<=(const Time &lhs, const Time &rhs)
{
    return lhs.total_minutes() <= rhs.total_minutes();
}

bool operator==(const Time &lhs, const Time &rhs)
{
    return lhs.total_minutes() == rhs.total_minutes();
}

int Time::total_minutes() const
{
    return _hours * 60 + _minutes;
}

bool operator<(const Time &lhs, const Time &rhs)
{
    return lhs.total_minutes() < rhs.total_minutes();
}
bool operator>(const Time &lhs, const Time &rhs)
{
    return lhs.total_minutes() > rhs.total_minutes();
}

Time operator-(const Time &lhs, const Time &rhs)
{
    Time time(0,0);

    int hours = abs(lhs.hours() - rhs.hours()) % 24;
    int minutes = lhs.minutes() - rhs.minutes();

    if(minutes < 0)
    {
        --hours;
        minutes += 60;
    }

    time.setHours(hours);
    time.setMinutes(minutes);

    return time;
}

Time operator+(const Time &lhs, const Time &rhs)
{
    Time time(0,0);

    time.setHours( (lhs.hours() + rhs.hours()) % 24);
    time.setHours( time.hours() + (lhs.minutes() + rhs.minutes()) / 60 );
    time.setMinutes( (lhs.minutes() + rhs.minutes()) % 60);

    return time;
}

