#ifndef SHIFT_H
#define SHIFT_H

#include "../lesson/lesson.h"
#include <vector>

class Shift
{
public:
    Shift();

    bool isEnable() const;
    void setEnable(bool value);

    size_t getNumber_of_lessons() const;

    void addLesson(const Lesson &lesson);
    void remove_lesson(int index);

    std::vector<Lesson> _lessons;
    int getStart_number_of_lesson() const;
    void setStart_number_of_lesson(int start_number_of_lesson);

private:
    bool _enable;
    int _start_number_of_lesson;
};

#endif // SHIFT_H
