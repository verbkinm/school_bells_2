#include <algorithm>
#include <iostream>
#include <QString>
#include "current_shedule.h"

#define TIMER_INTERVAL 1000

Current_Shedule::Current_Shedule(std::shared_ptr<const Settings> settings, QObject *parent) :
    QObject (parent),
    _spSettings(settings)
{
    connect(&_timer, SIGNAL(timeout()), SLOT(slotTimer_out()));
    _timer.setInterval(TIMER_INTERVAL);
    _timer.start();
}

void Current_Shedule::add(const Time_of_day &time, const std::string &sound)
{
    _call_table.insert({time, sound});
    setNext_call_according_local_time();
}

void Current_Shedule::printTable() const
{
    std::cout << "Shedule table:" << std::endl;
    int number = 0;
    for( const auto &[time, sound] : _call_table)
    {
        if(_current_iterator->first == time)
            std::cout << "*";
        std::cout << number++ << ": " << time.toString() << " - " << sound << std::endl;
    }
}

void Current_Shedule::setNext_call_according_local_time()
{
    _current_iterator = std::find_if(_call_table.begin(), _call_table.end(),
                                     [] (const std::pair<Time_of_day, std::string> pair)
                                        { return pair.first >= Time_of_day::fromLocal_time();});
    circularity_of_iterator();
}

void Current_Shedule::circularity_of_iterator()
{
    if(_current_iterator == _call_table.end() && _call_table.size())
        _current_iterator = _call_table.begin();
}

void Current_Shedule::fill_current_shedule()
{
    _call_table.clear();
    for(const auto &shift : _spSettings->shedule_of_day()._shifts)
    {
        if(shift.isEnable())
            fill_shifts(shift);
    }
}

void Current_Shedule::fill_shifts(const Shift &shift)
{
    for (const auto &lesson : shift._lessons)
    {
        if(lesson.isEnable())
        {
            if(_spSettings->general()->getCall_before_lesson())
                add(lesson.getTime_begin() - Time_of_day(0, _spSettings->general()->getNumber_of_minutes_to_call_before_lesson()), _spSettings->general()->getSound_before_lesson());
            add(lesson.getTime_begin(), lesson.getSound_begin());
            add(lesson.getTime_end(), lesson.getSound_end());
        }
    }
}

void Current_Shedule::slotTimer_out()
{
    if(Time_of_day::fromLocal_time() == _current_iterator->first)
    {
        _cmd.exec(_spSettings->general()->getPrograms_before_bell());
        this->_player.play(_current_iterator->second);
        _cmd.exec(_spSettings->general()->getPrograms_after_bell());
        _current_iterator++;
        circularity_of_iterator();
    }
}

void Current_Shedule::update()
{
    _timer.stop();
    fill_current_shedule();
    _timer.start();
    printTable();
}
