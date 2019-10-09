#include <algorithm>
#include <iostream>
#include <QString>
#include <QDebug>
#include "current_shedule.h"

void Current_Shedule::callback(Current_Shedule& shedule, Timer &tr, std::chrono::milliseconds delay)
{
    std::lock_guard<std::mutex> lock(tr.m_changing_mutex);
    if(tr._stoped)
        return;

    std::cout << shedule._current_iterator->first.toString() << std::endl;
    if(Time::fromLocal_time() == shedule._current_iterator->first)
    {
        shedule._current_iterator++;
        shedule.circularity_of_iterator();
    }

    std::this_thread::sleep_for(delay);

    void (*func)(Current_Shedule&, Timer&, std::chrono::milliseconds);
    func = callback;

    lock.~lock_guard();
    tr.start(func, shedule);
}

Current_Shedule::Current_Shedule()
{

}

void Current_Shedule::add(const Time &time, const std::string &sound)
{
    _call_table.insert({time, sound});
    setNext_call_according_local_time();
}

Call Current_Shedule::getNext_call() const
{
    check_shedule_size();
    return {_current_iterator->first, _current_iterator->second};
}

Call Current_Shedule::getLast_call()
{
    check_shedule_size();
    auto it = _current_iterator;
    if(it == _call_table.begin())
        it = --(_call_table.end());

    Call call(it->first, it->second);
    return call;
}

void Current_Shedule::printTable() const
{
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
                           [] (const std::pair<Time, std::string> pair)
//                           { return pair.first >= Time(8,50)/*Time::fromLocal_time()*/;});
                           { return pair.first >= Time::fromLocal_time();});
    circularity_of_iterator();
}

void Current_Shedule::circularity_of_iterator()
{
    if(_current_iterator == _call_table.end() && _call_table.size())
        _current_iterator = _call_table.begin();
}

void Current_Shedule::clear()
{
    _timer.stop();
    _call_table.clear();
}

void Current_Shedule::watch()
{
    void (*func)(Current_Shedule&, Timer&, std::chrono::milliseconds);
    func = callback;
    _timer.start(func, *this);
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
