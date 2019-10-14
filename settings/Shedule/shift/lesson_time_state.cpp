#include "lesson_time_state.h"
#include "../../../circular_vector.h"


Lesson_Time_State::Lesson_Time_State(const std::vector<Lesson> &lessons) :
    _isLesson_now(false), _current_or_next_lesson_number(0), _lessons(lessons), _off(true)
{
    Time current_time = Time::fromLocal_time();
    Circular_Vector<Lesson> cv(lessons);

    Lesson current_lesson, next_lesson, previos_lesson;

    for(size_t lesson_number = 0; lesson_number < cv.size(); ++lesson_number)
    {
        current_lesson = cv.at(lesson_number);
        next_lesson = current_lesson;
        previos_lesson = current_lesson;

        if(!current_lesson.isEnable())
            continue;

        if(current_lesson.isTime_corresponds_to_lesson(current_time))
        {
            _isLesson_now = true;
            _current_or_next_lesson_number = lesson_number;
            _time_left = current_lesson.getTime_end() - current_time;
            _off = false;
            break;
        }

        while(cv.next()->getTime_begin() != current_lesson.getTime_begin())
        {
            next_lesson = *cv.iterrator();
            if(!next_lesson.isEnable())
                continue;
        }
        for(size_t next_lesson_number = lesson_number; next_lesson_number < cv.size(); ++next_lesson_number)
        {
            next_lesson = cv.at(next_lesson_number);
            if(!cv.next_iterrator()->isEnable())
                continue;

            for(size_t previos_lesson_number = lesson_number; previos_lesson_number < cv.size(); --previos_lesson_number)
            {

            }
        }
        //        else if(cv.next_iterrator()->isEnable() && current_time < cv.next_iterrator()->getTime_begin() && current_time > cv.previos_iterrator()->getTime_end())
        //        {
        //            _isLesson_now = false;
        //            _current_or_next_lesson_number = (lesson_number+1 >= _lessons.size()) ? 0 : lesson_number+1 ;
        //            _time_left = lesson.getTime_end() - current_time;
        //            _off = false;
        //        }

    }
}

bool Lesson_Time_State::next_lesson_is_enabled(size_t current_lesson_number)
{
    try
    {
        if(_lessons.at(current_lesson_number+1).isEnable())
            return true;
    }
    catch(std::out_of_range &)
    {
        return false;
    }

    return false;
}

bool Lesson_Time_State::isOff() const
{
    return _off;
}
