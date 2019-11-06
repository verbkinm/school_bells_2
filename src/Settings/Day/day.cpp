#include <ctime>

#include "day.h"


Day::Day() :  _enable(false), _number_shedule_of_day(0)
{

}

size_t Day::current_day_of_week()
{
    time_t rawtime;
    tm * timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    return static_cast<size_t>(timeinfo->tm_wday);
}

bool Day::isEnable() const
{
    return _enable;
}

void Day::setEnable(bool enable)
{
    _enable = enable;
}

size_t Day::getNumber_shedule_of_day() const
{
    return _number_shedule_of_day;
}

void Day::setNumber_shedule_of_day(size_t number_shedule_of_day)
{
    _number_shedule_of_day = number_shedule_of_day;
}
