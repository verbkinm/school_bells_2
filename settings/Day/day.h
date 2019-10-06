#ifndef DAYS_H
#define DAYS_H

#include <string>

class Day
{
public:
    Day();

    static size_t current_day_of_week();

    bool isEnable() const;
    void setEnable(bool isEnable);

    size_t getNumber_shedule_of_day() const;
    void setNumber_shedule_of_day(size_t getNumber_shedule_of_day);

//    const std::string DAY[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

private:
    bool _enable;
    size_t _number_shedule_of_day;
};

#endif // DAYS_H
