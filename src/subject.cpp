#include "subject.h"

Subject::Subject()
{

}

void Subject::attach(Observer  *observer)
{
    _observers.push_back(observer);
}

void Subject::detache(Observer  *observer)
{
    _observers.remove(observer);
}

void Subject::notify()
{
    for(auto observer : _observers)
        observer->update();
}
