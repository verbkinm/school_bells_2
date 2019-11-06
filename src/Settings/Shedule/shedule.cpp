#include "shedule.h"

Shedule::Shedule()
{

}

std::string Shedule::name() const
{
    return _name;
}

void Shedule::setName(const std::string &name)
{
    _name = name;
}
