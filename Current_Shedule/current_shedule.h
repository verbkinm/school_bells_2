#ifndef CURRENT_SHEDULE_H
#define CURRENT_SHEDULE_H

#include <map>
#include <QTimer>
#include "../timer.h"
#include "call.h"

class Current_Shedule
{
public:
    static void callback(Current_Shedule& shedule, Timer &tr, std::chrono::milliseconds delay);

    Current_Shedule();

    void add(const Time &time, const std::string &sound);
    void clear();

    Call getNext_call() const;
    Call getLast_call();

    void printTable() const;
    void watch();
    void unwatch();

private:
    void check_shedule_size() const;
    void setNext_call_according_local_time();
    void circularity_of_iterator();

    std::map<Time, std::string> _call_table;
    std::map<Time, std::string>::iterator _current_iterator;
    Timer _timer;
};

#endif // CURRENT_SHEDULE_H
