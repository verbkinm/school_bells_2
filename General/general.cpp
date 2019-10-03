#include "general.h"

General::General() : _manual_call("нет"), _sound_dir_path ("sounds")
{

}

std::string General::getManual_call() const
{
    return _manual_call;
}

void General::setManual_call(const std::string &manual_call)
{
    _manual_call = manual_call;
}

std::string General::getSound_dir_path() const
{
    return _sound_dir_path;
}

void General::setSound_dir_path(const std::string &sound_dir_path)
{
    _sound_dir_path = sound_dir_path;
}
