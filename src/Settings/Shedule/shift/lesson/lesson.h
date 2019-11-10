#ifndef LESSON_H
#define LESSON_H

#include <string>
#include "time_of_day.h"

class Lesson
{
public:
    Lesson();

    bool isEnable() const;
    void setEnable(bool value);

    std::string getSound_begin() const;
    void setSound_begin(const std::string &value);

    std::string getSound_end() const;
    void setSound_end(const std::string &value);

    Time_of_day getTime_begin() const;
    void setTime_begin(const Time_of_day &time_begin);

    Time_of_day getTime_end() const;
    void setTime_end(const Time_of_day &time_end);

//    bool isTime_corresponds_to_lesson(const Time_of_day &time) const;

private:
    bool enable;

    std::string sound_begin;
    std::string sound_end;

    Time_of_day _time_begin;
    Time_of_day _time_end;
};

#endif // LESSON_H
