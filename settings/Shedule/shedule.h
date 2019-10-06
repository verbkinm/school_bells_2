#ifndef SHEDULE_H
#define SHEDULE_H

#include "shift/shift.h"
#include <string>

class Shedule
{
public:
    Shedule();

    std::vector<Shift> _shifts;

    std::string name() const;
    void setName(const std::string &name);

private:
    std::string _name;
};

#endif // SHEDULE_H
