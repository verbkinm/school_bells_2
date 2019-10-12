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

Time Lesson::getTime_begin() const
{
    return _time_begin;
}

void Lesson::setTime_begin(const Time &time_begin)
{
    _time_begin = time_begin;
}

Time Lesson::getTime_end() const
{
    return _time_end;
}

void Lesson::setTime_end(const Time &time_end)
{
    _time_end = time_end;
}

std::string Lesson::getTime_begin_str() const
{
    return _time_begin.toString();
}

std::string Lesson::getTime_end_str() const
{
    return _time_end.toString();
}

