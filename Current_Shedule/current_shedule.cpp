#include <algorithm>
#include "current_shedule.h"

Current_Shedule::Current_Shedule()
{

}

void Current_Shedule::add(const Time &time, const std::string &sound)
{
    _call_table.insert({time, sound});
    setNext_call_according_local_time();
}

Call Current_Shedule::getNext_call()
{
    check_shedule_size();
    return {_current_iterator->first, _current_iterator->second};
}

Call Current_Shedule::getLast_call()
{
    check_shedule_size();
    auto it = _current_iterator;
    if(it == _call_table.begin())
        it = --_call_table.end();

    Call call(it->first, it->second);
    return call;
}

void Current_Shedule::setNext_call_according_local_time()
{
    _current_iterator = std::find_if(_call_table.begin(), _call_table.end(),
                           [] (const std::pair<Time, std::string> pair)
//                           { return pair.first >= Time(8,50)/*Time::fromLocal_time()*/;});
                           { return pair.first >= Time::fromLocal_time();});

    if(_current_iterator == _call_table.end() && _call_table.size())
        _current_iterator = _call_table.begin();
}

//const std::map<Time, std::string> *Current_Shedule::table() const
//{
//    return &_call_table;
//}

void Current_Shedule::clear()
{
    _call_table.clear();
}

void Current_Shedule::check_shedule_size()
{
    if(_call_table.size() == 0)
        throw std::out_of_range("Call_table size is 0");
}
