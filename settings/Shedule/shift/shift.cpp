#include <iostream>

#include "shift.h"

Shift::Shift() : _enable(false), _start_number_of_lesson(1)
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

int Shift::getStart_number_of_lesson() const
{
    return _start_number_of_lesson;
}

void Shift::setStart_number_of_lesson(int start_number_of_lesson)
{
    _start_number_of_lesson = start_number_of_lesson;
}
