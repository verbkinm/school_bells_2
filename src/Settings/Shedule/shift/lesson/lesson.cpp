#include "lesson.h"

Lesson::Lesson() : enable(false), sound_begin("NONE"), sound_end("NONE")
{
}

bool Lesson::isEnable() const
{
    return enable;
}

void Lesson::setEnable(bool value)
{
    enable = value;
}

std::string Lesson::getSound_begin() const
{
    return sound_begin;
}

void Lesson::setSound_begin(const std::string &value)
{
    sound_begin = value;
}

std::string Lesson::getSound_end() const
{
    return sound_end;
}

void Lesson::setSound_end(const std::string &value)
{
    sound_end = value;
}

Time_of_day Lesson::getTime_begin() const
{
    return _time_begin;
}

void Lesson::setTime_begin(const Time_of_day &time_begin)
{
    _time_begin = time_begin;
}

Time_of_day Lesson::getTime_end() const
{
    return _time_end;
}

void Lesson::setTime_end(const Time_of_day &time_end)
{
    _time_end = time_end;
}

//bool Lesson::isTime_corresponds_to_lesson(const Time_of_day &time) const
//{
//    if((time >= _time_begin && time < _time_end) || (time <= _time_end && time > _time_begin))
//        return true;
//    return false;
//}

