#ifndef GENERAL_H
#define GENERAL_H

#include <string>

class General
{
public:
    General();

    std::string getManual_call() const;
    void setManual_call(const std::string &manual_call);

    std::string getSound_dir_path() const;
    void setSound_dir_path(const std::string &sound_dir_path);

    bool getCall_before_lesson() const;
    void setCall_before_lesson(bool call_before_lesson);

    int getNumber_of_minutes_to_call_before_lesson() const;
    void setNumber_of_minutes_to_call_before_lesson(int number_of_minutes_to_call_before_lesson);

    std::string getSound_before_lesson() const;
    void setSound_before_lesson(const std::string &sound_before_lesson);

private:
    std::string _manual_call;
    std::string _sound_dir_path;

    bool _call_before_lesson;
    int _number_of_minutes_to_call_before_lesson;
    std::string _sound_before_lesson;
};

#endif // GENERAL_H
