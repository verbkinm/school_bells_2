#include "call.h"

Call::Call(const Time &time, const std::string &sound) : _time(time), _sound(sound)
{

}

Time Call::time() const
{
    return _time;
}

void Call::setTime(const Time &time)
{
    _time = time;
}

std::string Call::sound() const
{
    return _sound;
}

void Call::setSound(const std::string &sound)
{
    _sound = sound;
}
