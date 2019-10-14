#ifndef LESSON_TIME_STATE_H
#define LESSON_TIME_STATE_H

#include <vector>
#include "../lesson/lesson.h"
#include "../time/time.h"

class Lesson_Time_State
{
public:
    Lesson_Time_State(const std::vector<Lesson> &lessons);

    bool isOff() const;

private:
    bool next_lesson_is_enabled(size_t current_lesson_number);

    bool _isLesson_now;
    size_t _current_or_next_lesson_number;
    Time _time_left;
    const std::vector<Lesson> &_lessons;

    bool _off;

};

#endif // LESSON_TIME_STATE_H
