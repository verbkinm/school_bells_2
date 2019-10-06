#ifndef CALL_H
#define CALL_H

#include "Settings/Shedule/time/time.h"

class Call
{
public:
    Call(const Time &time, const std::string &sound);

    Time time() const;
    void setTime(const Time &time);

    std::string sound() const;
    void setSound(const std::string &sound);

private:
    Time _time;
    std::string _sound;

};

#endif // CALL_H
