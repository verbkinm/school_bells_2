#ifndef TIME_OF_DAY_H
#define TIME_OF_DAY_H

#include <string>

class Time_of_day
{
public:
    static Time_of_day fromLocal_time();

    Time_of_day();
    Time_of_day(int h, int m);

    int hours() const;
    int minutes() const;

    void setHours(int h);
    void setMinutes(int m);

    void setFrom_string(std::string str);
    std::string toString() const;

    friend Time_of_day operator+(const Time_of_day &lhs, const Time_of_day &rhs);
    friend Time_of_day operator-(const Time_of_day &lhs, const Time_of_day &rhs);
    friend bool operator<(const Time_of_day &lhs, const Time_of_day &rhs);
    friend bool operator>(const Time_of_day &lhs, const Time_of_day &rhs);
    friend bool operator==(const Time_of_day &lhs, const Time_of_day &rhs);
    friend bool operator!=(const Time_of_day &lhs, const Time_of_day &rhs);
    friend bool operator<=(const Time_of_day &lhs, const Time_of_day &rhs);
    friend bool operator>=(const Time_of_day &lhs, const Time_of_day &rhs);

private:
    int total_minutes() const;

    char _hours;
    char _minutes;
};

#endif // TIME_OF_DAY_H
