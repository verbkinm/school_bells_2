#ifndef DAYS_H
#define DAYS_H

#include <string>

class Day
{
public:
    Day();

    bool getCall_before_lesson() const;
    void setCall_before_lesson(bool getCall_before_lesson);

    int getNumber_of_minutes_to_call_before_lesson() const;
    void setNumber_of_minutes_to_call_before_lesson(int getNumber_of_minutes_to_call_before_lesson);

    bool isEnable() const;
    void setEnable(bool isEnable);

    int getNumber_shedule_of_day() const;
    void setNumber_shedule_of_day(int getNumber_shedule_of_day);

    std::string getSound_before_lesson() const;
    void setSound_before_lesson(const std::string &getSound_before_lesson);

private:
    bool _call_before_lesson;
    int _number_of_minutes_to_call_before_lesson;

    bool _enable;
    int _number_shedule_of_day;

    std::string _sound_before_lesson;
};

#endif // DAYS_H
