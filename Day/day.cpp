#include "day.h"

Day::Day() : _call_before_lesson(false), _number_of_minutes_to_call_before_lesson(0),
    _enable(false), _number_shedule_of_day(0), _sound_before_lesson("нет")
{

}

bool Day::getCall_before_lesson() const
{
    return _call_before_lesson;
}

void Day::setCall_before_lesson(bool call_before_lesson)
{
    _call_before_lesson = call_before_lesson;
}

int Day::getNumber_of_minutes_to_call_before_lesson() const
{
    return _number_of_minutes_to_call_before_lesson;
}

void Day::setNumber_of_minutes_to_call_before_lesson(int number_of_minutes_to_call_before_lesson)
{
    if(number_of_minutes_to_call_before_lesson < 1)
    {
        _number_of_minutes_to_call_before_lesson = 1;
        return;
    }
    _number_of_minutes_to_call_before_lesson = number_of_minutes_to_call_before_lesson;
}

bool Day::isEnable() const
{
    return _enable;
}

void Day::setEnable(bool enable)
{
    _enable = enable;
}

int Day::getNumber_shedule_of_day() const
{
    return _number_shedule_of_day;
}

void Day::setNumber_shedule_of_day(int number_shedule_of_day)
{
    _number_shedule_of_day = number_shedule_of_day;
}

std::string Day::getSound_before_lesson() const
{
    return _sound_before_lesson;
}

void Day::setSound_before_lesson(const std::string &sound_before_lesson)
{
    if(sound_before_lesson.empty() || sound_before_lesson == "")
    {
        _sound_before_lesson = "NONE";
        return;
    }
    _sound_before_lesson = sound_before_lesson;
}
