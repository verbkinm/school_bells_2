#include <iostream>

#include "shift.h"

Shift::Shift() : _enable(false)
{

}

bool Shift::isEnable() const
{
    return _enable;
}

void Shift::setEnable(bool value)
{
    _enable = value;
}

size_t Shift::getNumber_of_lessons() const
{
    return _lessons.size();
}

void Shift::addLesson(const Lesson &lesson)
{
    _lessons.push_back(lesson);
}

void Shift::remove_lesson(int index)
{
    try
    {
        _lessons.erase(_lessons.begin() + index);
    }
    catch (std::out_of_range &e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}
