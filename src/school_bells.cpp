#include "school_bells.h"

#define TIMER_INTERVAL 1000
#define WRONG_DAY_OF_WEEK 100

#define VERSION "0.14.3.4"

School_bells::School_bells(QObject *parent) : QObject (parent),
    _spSettings(std::make_shared<Settings>()),
    _current_shedule(_spSettings),
    _current_day_of_week(WRONG_DAY_OF_WEEK)
{
    Log::write(std::string("Start program " + std::string("version ") + std::string(VERSION)));

    if(_spSettings->network().isEnable())
        _spWeb_socket_server = std::make_unique<Web_socket_server>(_spSettings);

    connect(&_day_timer, SIGNAL(timeout()), SLOT(slotNew_day()));
    create_day_shedule();
}

School_bells::~School_bells()
{
    Log::write("Stop program");
}

void School_bells:: create_day_shedule()
{
    _day_timer.stop();
    _current_shedule.update();
    _current_day_of_week = Day::current_day_of_week();
    _day_timer.start(TIMER_INTERVAL);
}

void School_bells::slotNew_day()
{
    if(_current_day_of_week == Day::current_day_of_week())
        return;
    create_day_shedule();
}

void School_bells::slotCreate_day_shedule()
{
    create_day_shedule();
}
