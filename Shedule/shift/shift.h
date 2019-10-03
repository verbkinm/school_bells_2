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
private:
    bool _enable;
};

#endif // SHIFT_H
