#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include "list"

class Subject
{
public:
    Subject();

    void attach(Observer *observer);
    void detache(Observer *observer);

    void notify();

private:
    std::list<Observer *> _observers;
};

#endif // SUBJECT_H
