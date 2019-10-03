#ifndef TIME_H
#define TIME_H

#include <string>

class Time
{
public:
    Time();
    Time(int h, int m);

    int hours() const;
    int minutes() const;

    void setHours(int h);
    void setMinutes(int m);

    void setFrom_string(std::string str);
    std::string getString() const;

    friend Time operator+(const Time &lhs, const Time &rhs);
    friend Time operator-(const Time &lhs, const Time &rhs);

private:
    char _hours;
    char _minutes;
};

#endif // TIME_H

