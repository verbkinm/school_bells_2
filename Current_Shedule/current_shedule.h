#ifndef CURRENT_SHEDULE_H
#define CURRENT_SHEDULE_H

#include <map>
#include "call.h"

class Current_Shedule
{
public:
    Current_Shedule();

    void add(const Time &time, const std::string &sound);

    Call getNext_call();
    Call getLast_call();

//    const std::map<Time, std::string> *table() const;

    void clear();

private:
    void check_shedule_size();
    void setNext_call_according_local_time();

    std::map<Time, std::string> _call_table;
    std::map<Time, std::string>::iterator _current_iterator;
};

#endif // CURRENT_SHEDULE_H
