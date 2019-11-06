#include <algorithm>
#include <iostream>
#include <QString>
#include "current_shedule.h"

Current_Shedule::Current_Shedule(std::shared_ptr<const Settings> settings, QObject *parent) :
    QObject (parent),
    _spSettings(settings)
{
    connect(&_timer, SIGNAL(timeout()), SLOT(slotTimer_out()));
}

void Current_Shedule::add(const Time_of_day &time, const std::string &sound)
{
    _call_table.insert({time, sound});
    setNext_call_according_local_time();
}

void Current_Shedule::remove(const Time_of_day &time)
{
    _call_table.erase(time);
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

void Current_Shedule::clear()
{
    _timer.stop();
    _call_table.clear();
}

void Current_Shedule::watch()
{
    _timer.start(1000);
}

void Current_Shedule::unwatch()
{
    _timer.stop();
}

void Current_Shedule::check_shedule_size() const
{
    if(_call_table.size() == 0)
        throw std::out_of_range("Call_table size is 0");
}
