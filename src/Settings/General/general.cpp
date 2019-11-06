#include <sstream>
#include "general.h"

General::General() : _manual_call("нет"), _sound_dir_path ("sounds"),
    _call_before_lesson(false), _number_of_minutes_to_call_before_lesson(1),
    _sound_before_lesson("нет")
{

}

std::string General::getManual_call() const
{
    return _manual_call;
}

void General::setManual_call(const std::string &manual_call)
{
    _manual_call = manual_call;
}

std::string General::getSound_dir_path() const
{
    return _sound_dir_path;
}

void General::setSound_dir_path(const std::string &sound_dir_path)
{
    _sound_dir_path = sound_dir_path;
}

bool General::getCall_before_lesson() const
{
    return _call_before_lesson;
}

void General::setCall_before_lesson(bool call_before_lesson)
{
    _call_before_lesson = call_before_lesson;
}

int General::getNumber_of_minutes_to_call_before_lesson() const
{
    return _number_of_minutes_to_call_before_lesson;
}

void General::setNumber_of_minutes_to_call_before_lesson(int number_of_minutes_to_call_before_lesson)
{
    if(number_of_minutes_to_call_before_lesson < 1)
        number_of_minutes_to_call_before_lesson = 1;
    _number_of_minutes_to_call_before_lesson = number_of_minutes_to_call_before_lesson;
}

std::string General::getSound_before_lesson() const
{
    return _sound_before_lesson;
}

void General::setSound_before_lesson(const std::string &sound_before_lesson)
{
    _sound_before_lesson = sound_before_lesson;
}

std::string General::getPrograms_before_bell() const
{
    return _programs_before_bell;
}

void General::setPrograms_before_bell(const std::string &value)
{
    _programs_before_bell = value;
}

std::string General::getPrograms_after_bell() const
{
    return _programs_after_bell;
}

void General::setPrograms_after_bell(const std::string &value)
{
    _programs_after_bell = value;
}
