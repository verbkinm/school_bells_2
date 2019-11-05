#include "school_bells.h"

#define TIMER_INTERVAL 1000
#define WRONG_DAY_OF_WEEK 100

#define VERSION 0.13

School_bells::School_bells(QObject *parent) : QObject (parent),
    _spSettings(std::make_shared<Settings>()),
    _current_shedule(_spSettings),
    _current_day_of_week(WRONG_DAY_OF_WEEK)
{
    Log::write("Start program");

    connect(&_day_timer, SIGNAL(timeout()), SLOT(slotNew_day()));
    slotNew_day();

    if(_spSettings->network()->isEnable())
    {
        _spWeb_socket_server = std::make_unique<Web_socket_server>(_spSettings, QHostAddress(_spSettings->network()->getAddr().c_str()), _spSettings->network()->getPort());
        connect(_spWeb_socket_server.get(), SIGNAL(settingsChanged()), SLOT(slotCreate_day_shedule()));
    }
}

School_bells::~School_bells()
{
    Log::write("Stop program");
}

void School_bells::fill_current_shedule()
{
    _current_shedule.unwatch();
    _current_shedule.clear();
    for(const auto &shift : _spSettings->shedule_of_day()._shifts)
    {
        if(shift.isEnable())
            fill_shifts(shift);
    }
}

void School_bells::fill_shifts(const Shift &shift)
{
    for (const auto &lesson : shift._lessons)
    {
        if(lesson.isEnable())
        {
            if(_spSettings->general()->getCall_before_lesson())
                _current_shedule.add(lesson.getTime_begin() - Time(0, _spSettings->general()->getNumber_of_minutes_to_call_before_lesson()), _spSettings->general()->getSound_before_lesson());
            _current_shedule.add(lesson.getTime_begin(), lesson.getSound_begin());
            _current_shedule.add(lesson.getTime_end(), lesson.getSound_end());
        }
    }
}

void School_bells::create_day_shedule()
{
    _day_timer.stop();

    fill_current_shedule();

    _current_shedule.watch();
    _current_shedule.printTable();

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
