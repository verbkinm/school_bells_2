#ifndef LESSON_H
#define LESSON_H

#include <string>
#include "../time/time.h"

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

    Time getTime_begin() const;
    void setTime_begin(const Time &time_begin);

    Time getTime_end() const;
    void setTime_end(const Time &time_end);

    std::string getTime_begin();
    std::string getTime_end();

private:
    bool enable;

    std::string sound_begin;
    std::string sound_end;

    Time _time_begin;
    Time _time_end;
};

#endif // LESSON_H
